import requests
import os
import sys
import subprocess
from datetime import datetime

def download_apk():
    repo_owner = "rdfdd47-jpg"
    repo_name = "snes-emulator"
    api_url = f"https://api.github.com/repos/{repo_owner}/{repo_name}"
    
    print("\n🎮 SNES Emulator APK Downloader")
    print("================================\n")
    
    print("📡 Fetching latest release...")
    
    try:
        # Get latest release
        response = requests.get(f"{api_url}/releases/latest")
        response.raise_for_status()
        release_data = response.json()
        
        # Check for errors
        if "message" in release_data and release_data["message"] == "Not Found":
            print("❌ No releases found. Please create a release first.")
            print(f"   Visit: https://github.com/{repo_owner}/{repo_name}/releases")
            return False
        
        # Find APK asset
        apk_url = None
        apk_name = None
        
        for asset in release_data.get("assets", []):
            if asset["name"].endswith(".apk"):
                apk_url = asset["browser_download_url"]
                apk_name = asset["name"]
                break
        
        if not apk_url:
            print("❌ No APK found in the latest release.")
            return False
        
        tag_name = release_data.get("tag_name", "Unknown")
        release_name = release_data.get("name", tag_name)
        
        print(f"✅ Found release: {release_name} ({tag_name})")
        print(f"📥 Downloading APK: {apk_name}...\n")
        
        # Download APK
        filename = f"snes-emulator-{datetime.now().strftime('%Y%m%d')}.apk"
        
        response = requests.get(apk_url, stream=True)
        response.raise_for_status()
        
        total_size = int(response.headers.get('content-length', 0))
        downloaded = 0
        
        with open(filename, 'wb') as f:
            for chunk in response.iter_content(chunk_size=8192):
                if chunk:
                    downloaded += len(chunk)
                    f.write(chunk)
                    if total_size:
                        percent = (downloaded / total_size) * 100
                        print(f"Progress: {percent:.1f}% ({downloaded / 1024 / 1024:.1f} MB)", end='\r')
        
        print(f"\n\n✅ Downloaded: {filename}")
        
        # Check for adb
        try:
            subprocess.run(["adb", "version"], capture_output=True, check=True)
            print("\n🔌 Android device detected (adb found)")
            
            install = input("Would you like to install the APK now? (y/n): ").strip().lower()
            if install == 'y':
                subprocess.run(["adb", "install", "-r", filename], check=True)
                print("✅ Installation complete!")
        except:
            print("\n💡 To install manually:")
            print("   1. Transfer the APK file to your Android device")
            print("   2. Open the file and tap 'Install'")
            print("   3. Enable 'Unknown Sources' if prompted")
            print(f"\n💡 Or use adb:")
            print(f"   adb install {filename}")
        
        print(f"\n📁 APK saved to: {os.path.abspath(filename)}\n")
        return True
        
    except requests.exceptions.RequestException as e:
        print(f"❌ Error: {e}")
        return False
    except Exception as e:
        print(f"❌ Unexpected error: {e}")
        return False

if __name__ == "__main__":
    success = download_apk()
    sys.exit(0 if success else 1)
