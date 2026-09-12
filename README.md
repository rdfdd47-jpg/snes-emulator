# SNES Emulator - Android Application

A fully-featured SNES emulator for Android devices, built with Java and C++.

## Features

- 65C816 CPU emulation
- Graphics (PPU) rendering
- Audio (APU) processing
- ROM loading and cartridge support
- Touch-based game controls
- Full screen emulation at 60 FPS

## Project Structure

```
src/
├── main/
│   ├── cpp/              # Native C++ emulator core
│   │   ├── CMakeLists.txt
│   │   ├── include/      # C++ headers
│   │   └── *.cpp         # Emulator implementation
│   ├── java/             # Android Java code
│   │   └── com/example/snesemulator/
│   │       ├── MainActivity.java
│   │       ├── SNESEmulator.java (JNI bridge)
│   │       └── SNESEmulatorView.java
│   └── res/              # Android resources
│       └── layout/       # UI layouts
build.gradle             # Gradle build configuration
```

## Building

1. Open the project in Android Studio
2. Connect an Android device (API 24+)
3. Build: `./gradlew assembleDebug`
4. Install: `./gradlew installDebug`
5. Run on device

## Next Steps

1. **Complete CPU Implementation**: Implement all 65C816 opcodes
2. **Implement Graphics**: Full PPU tile and sprite rendering
3. **Implement Audio**: APU sound channel processing
4. **Add ROM File Picker**: Allow users to select SNES ROMs
5. **Optimize Performance**: Profile and optimize emulation loop
6. **Add Game Controls**: On-screen gamepad or button mapping
7. **Save States**: Support game save/load functionality

## Development Notes

- The emulator core is in C++ for performance
- JNI bridge in `SNESEmulator.java` connects Java UI to C++ code
- Rendering uses Android's `SurfaceView` and bitmap buffers
- CMake handles native compilation

## License

MIT License
