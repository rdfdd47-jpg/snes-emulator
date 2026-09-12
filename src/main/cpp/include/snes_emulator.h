#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <string>

// Forward declarations
class CPU;
class Memory;
class PPU;
class APU;
class Cartridge;

class SNESEmulator {
public:
    SNESEmulator();
    ~SNESEmulator();

    // ROM loading
    bool loadROM(const std::string& romPath);
    void unloadROM();

    // Emulation control
    void run();
    void pause();
    void reset();
    void step(); // Execute one cycle

    // Frame rendering
    void renderFrame(uint32_t* frameBuffer, int width, int height);

    // Input handling
    void handleInput(uint32_t button, bool pressed);

    // State
    bool isRunning() const { return running; }
    bool isROMLoaded() const { return romLoaded; }

private:
    std::unique_ptr<CPU> cpu;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<PPU> ppu;
    std::unique_ptr<APU> apu;
    std::unique_ptr<Cartridge> cartridge;

    bool running;
    bool romLoaded;
    uint64_t cycleCount;
};
