# SNES Emulator for Android

A SNES (Super Nintendo Entertainment System) emulator for Android built with C++ and JNI.

## Features
- 65816 CPU emulation
- Graphics rendering (PPU)
- Audio support (APU)
- ROM loading and cartridge support
- Save/Load state functionality (planned)

## Download APK

### Latest Release
- Download the latest APK from the [Releases page](https://github.com/rdfdd47-jpg/snes-emulator/releases)
- Look for `snes-emulator-release.apk` or the most recent version

### Automated Builds
- Each push to `main` generates a build artifact available in [Actions](https://github.com/rdfdd47-jpg/snes-emulator/actions)
- Tagged releases (v1.0, v1.1, etc.) are automatically published with downloadable APKs

### Installation
1. Download the APK file
2. Enable "Unknown Sources" in your Android settings
3. Open the APK file and tap "Install"
4. Or use adb: `adb install snes-emulator-release.apk`

## Building Locally

### Prerequisites
- Android SDK API 34 or higher
- Android NDK
- CMake
- Gradle
- JDK 17

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/rdfdd47-jpg/snes-emulator.git
cd snes-emulator

# Build Release APK
./gradlew assembleRelease

# Or build Debug APK
./gradlew assembleDebug

# Install on device
./gradlew installRelease
```

## Project Structure

```
snes-emulator/
├── .github/
│   └── workflows/          # GitHub Actions CI/CD
├── src/
│   └── main/
│       ├── cpp/            # C++ emulator core
│       │   ├── include/    # Header files
│       │   ├── CMakeLists.txt
│       │   └── *.cpp       # Implementation files
│       ├── java/           # Android Java code
│       ├── res/            # Android resources
│       └── AndroidManifest.xml
├── build.gradle            # Gradle build configuration
└── settings.gradle
```

## Architecture

- **CPU** - 65816 processor emulation
- **Memory** - Address space mapping and management
- **PPU** - Graphics processing and rendering
- **APU** - Audio processing and sound generation
- **JNI** - Java/C++ integration layer

## Development

The emulator is still in development. Current focus is on:
1. Implementing the full 65816 instruction set
2. Memory mapping and cartridge support
3. Graphics rendering
4. Audio generation

## Release Management

To create a new release:

```bash
# Tag your release
git tag -a v1.0 -m "Version 1.0"

# Push tag to GitHub
git push origin v1.0
```

This will automatically:
1. Build the APK
2. Create a GitHub Release
3. Upload the APK for download

## License

MIT License
