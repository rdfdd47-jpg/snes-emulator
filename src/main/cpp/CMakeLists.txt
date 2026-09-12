cmake_minimum_required(VERSION 3.22.1)
project(snes-emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the native library
add_library(snes-emulator-native SHARED
    cpu.cpp
    memory.cpp
    ppu.cpp
    apu.cpp
    rom_loader.cpp
    emulator.cpp
    jni_interface.cpp
)

# Include directories
target_include_directories(snes-emulator-native PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
