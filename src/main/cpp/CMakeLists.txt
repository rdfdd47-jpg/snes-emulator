cmake_minimum_required(VERSION 3.22.1)
project(snes-emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the emulator core library
add_library(snes-core SHARED
    snes_emulator.cpp
    cpu.cpp
    memory.cpp
    ppu.cpp
    apu.cpp
    cartridge.cpp
)

# Include directories
target_include_directories(snes-core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link against Android log library
find_library(log-lib log)
target_link_libraries(snes-core ${log-lib})
