@echo off
REM SNES Emulator APK Download Helper Script for Windows
REM Downloads the latest APK release from GitHub - FIXED VERSION

setlocal enabledelayedexpansion

set REPO=rdfdd47-jpg/snes-emulator
set API_URL=https://api.github.com/repos/%REPO%
set GITHUB_URL=https://github.com/%REPO%

cls
echo.
echo SNES Emulator APK Downloader
echo ==============================
echo.

echo Checking for latest release...
echo.

REM Create temp files
set TEMP_JSON=%TEMP%\gh_release_%RANDOM%.json
set TEMP_URL=%TEMP%\gh_url_%RANDOM%.txt

REM Download latest release info from GitHub API
curl -s -H "Accept: application/vnd.github.v3+json" "%API_URL%/releases/latest" > "%TEMP_JSON%"

REM Check if curl succeeded
if %ERRORLEVEL% NEQ 0 (
    echo Error: Failed to connect to GitHub API
    echo Please check your internet connection
    goto cleanup
)

REM Check if file was created and has content
if not exist "%TEMP_JSON%" (
    echo Error: Could not retrieve release information
    goto cleanup
)

REM Use PowerShell to parse JSON and extract APK URL
powershell -Command ^
    "$json = Get-Content -Raw '%TEMP_JSON%' | ConvertFrom-Json; " ^
    "$assets = $json.assets; " ^
    "$apk = $assets | Where-Object { $_.name -like '*.apk' } | Select-Object -First 1; " ^
    "if ($apk) { Write-Host $apk.browser_download_url } else { Exit 1 }"  > "%TEMP_URL%"

REM Check if URL was found
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: No APK file found in the latest release
    echo.
    echo Please ensure:
    echo  1. A release exists at: %GITHUB_URL%/releases
    echo  2. The release has an attached .apk file
    echo.
    echo Visit: %GITHUB_URL%/releases
    goto cleanup
)

REM Read the URL
set /p DOWNLOAD_URL=<"%TEMP_URL%"

REM Verify URL was read
if "!DOWNLOAD_URL!"=="" (
    echo Error: Could not extract download URL
    goto cleanup
)

echo Found release with APK file
echo.
echo Downloading: !DOWNLOAD_URL!
echo.

REM Generate filename with current date/time
for /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set DATESTR=%%c%%a%%b)
for /f "tokens=1-2 delims=/:" %%a in ('time /t') do (set TIMESTR=%%a%%b)
set FILENAME=snes-emulator-%DATESTR%-%TIMESTR%.apk

REM Download using PowerShell with proper error handling
echo Downloading to: %FILENAME%
powershell -Command ^
    "$ProgressPreference = 'SilentlyContinue'; " ^
    "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; " ^
    "try { " ^
    "(New-Object System.Net.WebClient).DownloadFile('!DOWNLOAD_URL!', '%FILENAME%'); " ^
    "Write-Host 'Download successful'; " ^
    "} catch { " ^
    "Write-Host 'Download failed: $($_.Exception.Message)'; " ^
    "Exit 1; " ^
    "}"

REM Check if download succeeded
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Download failed
    echo Please try again or download manually from:
    echo %GITHUB_URL%/releases
    echo.
    goto cleanup
)

if exist "%FILENAME%" (
    echo.
    echo ============================================
    echo  Download Complete!
    echo ============================================
    echo.
    echo File: %FILENAME%
    echo Location: %CD%\%FILENAME%
    echo Size: 
    for %%A in ("%FILENAME%") do (
        set /A SIZE=%%~zA / 1048576
        echo !SIZE! MB
    )
    echo.
    echo Installation Instructions:
    echo ------------------------------------
    echo Option 1 - USB Transfer:
    echo  1. Connect your Android device via USB
    echo  2. Transfer %FILENAME% to your device
    echo  3. Tap the file to install
    echo  4. If prompted, enable "Unknown Sources" in Settings
    echo.
    echo Option 2 - ADB Install:
    echo  adb install "%FILENAME%"
    echo.
    echo Option 3 - Manual Install:
    echo  1. Copy file to your device storage
    echo  2. Open file manager on device
    echo  3. Tap the APK file
    echo  4. Tap "Install"
    echo ============================================
    echo.
) else (
    echo.
    echo ERROR: Download file not found
    echo Download may have failed
    echo.
)

:cleanup
REM Clean up temp files
if exist "%TEMP_JSON%" del "%TEMP_JSON%"
if exist "%TEMP_URL%" del "%TEMP_URL%"

echo.
pause
endlocal
