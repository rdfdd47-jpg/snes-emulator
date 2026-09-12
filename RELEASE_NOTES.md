# SNES Emulator - Release Notes

## Version: Snes (Initial Release)
**Released:** September 12, 2026

---

## 🎮 About This Release

This is the **first public release** of the SNES Emulator - a cross-platform emulator for Super Nintendo Entertainment System (SNES) games, built with C++ backend and Android frontend support.

---

## ✨ Key Features

- **SNES CPU Emulation**: Full 65816 processor implementation
- **Memory Management**: Complete SNES address space handling
- **Graphics Rendering**: PPU (Picture Processing Unit) for authentic graphics
- **Audio Processing**: APU (Audio Processing Unit) with sound output
- **ROM Loading**: Support for SNES ROM file loading and execution
- **Android Port**: Native Android APK with Java-C++ JNI bridge
- **Cross-Platform Build**: CMake configuration for Windows, macOS, and Linux builds
- **Automated Downloads**: Helper scripts for easy APK distribution

---

## 📋 Changelog

### Core Emulator Components
- ✅ Added CPU implementation with 65816 processor support
- ✅ Added Memory header file with SNES address space definition
- ✅ Added PPU (Picture Processing Unit) for graphics rendering
- ✅ Added APU (Audio Processing Unit) for audio processing
- ✅ Added Emulator coordinator class for component management
- ✅ Added ROM loader utility functions

### Build & Configuration
- ✅ Added CMakeLists.txt for native C++ build configuration
- ✅ Added build.gradle with Android application configuration
- ✅ Added release build configuration to build.gradle
- ✅ Added JNI interface for Java-C++ communication

### Android Integration
- ✅ Added complete Android app structure
- ✅ Added AndroidManifest.xml with application metadata
- ✅ Added Java interface for seamless Java-C++ communication

### Developer Tools
- ✅ Added Python APK download helper script
- ✅ Added PowerShell APK download helper script for Windows
- ✅ Fixed APK download script with proper JSON parsing and error handling
- ✅ Added test APK build artifact for release

### Documentation
- ✅ Updated README with APK download instructions
- ✅ Added release workflow documentation

---

## 📥 Installation

### Android Users
Download the APK directly from the release assets and install on your Android device:

```bash
# Using PowerShell (Windows)
.\download_apk.ps1

# Using Python
python download_apk.py
```

### Desktop Users (Windows, macOS, Linux)
1. Clone the repository
2. Install CMake and compiler tools
3. Build from source:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

---

## 🏗️ Technical Details

### Architecture
- **Backend**: C++ with 65816 CPU emulation
- **Frontend**: Android (Java with JNI)
- **Build System**: CMake + Gradle
- **Rendering**: PPU-based graphics pipeline
- **Audio**: APU sound processor

### System Requirements
- **Android**: Android 5.0 (API 21) or higher
- **Desktop**: CMake 3.10+, C++11 compatible compiler

---

## ⚠️ Known Limitations

This is an **initial release** with the following limitations:
- Early-stage emulation - not all SNES games may run perfectly
- Performance optimization ongoing
- Additional game compatibility improvements planned

---

## 🐛 Bug Reports & Feedback

Found an issue? Have suggestions? Please open an issue on GitHub:
https://github.com/rdfdd47-jpg/snes-emulator/issues

---

## 📄 License

See LICENSE file in repository for details.

---

## 🙏 Acknowledgments

Thanks to the emulation community for documentation and resources that made this project possible.

---

**Happy Gaming! 🎮**
