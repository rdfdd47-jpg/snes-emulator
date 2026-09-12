@echo off
REM SNES Emulator APK Download Helper Script for Windows
REM Downloads the latest APK release from GitHub

setlocal enabledelayedexpansion
setlocal EnableDelayedExpansion

set REPO=rdfdd47-jpg/snes-emulator
set API_URL=https://api.github.com/repos/%REPO%

cls
echo.
echo SNES Emulator APK Downloader
echo ==============================
echo.

echo Checking for latest release...

REM Create temp file for JSON response
set TEMP_FILE=%TEMP%\gh_release.json
curl -s "%API_URL%/releases/latest" > "%TEMP_FILE%"

REM Check if file was created
if not exist "%TEMP_FILE%" (
    echo Error: Could not connect to GitHub
    pause
    exit /b 1
)

REM Look for APK URL in the JSON
for /f "tokens=*" %%a in ('findstr "browser_download_url.*\.apk" "%TEMP_FILE%"') do (
    set LINE=%%a
)

if "!LINE!"=="" (
    echo No releases found or no APK in latest release
    echo Visit: https://github.com/%REPO%/releases
    del "%TEMP_FILE%"
    pause
    exit /b 1
)

echo Found release
echo.
echo Downloading APK...
echo.

REM Generate filename with current date
for /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set DATESTR=%%c%%a%%b)
set FILENAME=snes-emulator-%DATESTR%.apk

REM Download from releases page
echo Connecting to GitHub...
powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; (New-Object System.Net.WebClient).DownloadFile('https://github.com/%REPO%/releases/latest/download/snes-emulator-release.apk', '%FILENAME%')}"

if exist "%FILENAME%" (
    echo.
    echo Download complete!
    echo File: %FILENAME%
    echo Location: %CD%\%FILENAME%
    echo.
    echo Installation Instructions:
    echo 1. Connect your Android device via USB
    echo 2. Or transfer the file and tap to install
    echo 3. If prompted, enable "Unknown Sources" in Settings
    echo.
    echo For ADB install:
    echo   adb install %FILENAME%
) else (
    echo Download failed. Please try again or visit:
    echo https://github.com/%REPO%/releases
)

del "%TEMP_FILE%"
pause
