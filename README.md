# SNES Emulator for Android

A SNES (Super Nintendo Entertainment System) emulator for Android built with C++ and JNI.

## Features
- 65816 CPU emulation
- Graphics rendering (PPU)
- Audio support (APU)
- ROM loading and cartridge support
- Save/Load state functionality (planned)

## Building

### Prerequisites
- Android SDK API 34 or higher
- Android NDK
- CMake
- Gradle

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/rdfdd47-jpg/snes-emulator.git
cd snes-emulator

# Build APK
./gradlew assembleDebug

# Install on device
./gradlew installDebug
```

## Project Structure

```
snes-emulator/
├── src/
│   └── main/
│       ├── cpp/              # C++ emulator core
│       │   ├── include/      # Header files
│       │   ├── CMakeLists.txt
│       │   └── *.cpp         # Implementation files
│       ├── java/             # Android Java code
│       ├── res/              # Android resources
│       └── AndroidManifest.xml
├── build.gradle              # Gradle build configuration
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

## License

MIT License
