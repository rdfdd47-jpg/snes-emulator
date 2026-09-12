#ifndef SNES_EMULATOR_H
#define SNES_EMULATOR_H

#include "cpu.h"
#include "memory.h"
#include "ppu.h"
#include "apu.h"
#include <cstdint>

class Emulator {
public:
    Emulator();
    ~Emulator();

    // Initialize emulator
    void init();

    // Load ROM file
    bool loadROM(const uint8_t* romData, size_t romSize);

    // Run one frame
    void runFrame();

    // Reset emulator
    void reset();

    // Get framebuffer for display
    const uint32_t* getFramebuffer() const;

    // Get audio buffer
    const int16_t* getAudioBuffer() const;
    int getAvailableSamples() const;

    // Pause/Resume
    void pause();
    void resume();

    // Check if running
    bool isRunning() const;

    // Save/Load state
    void saveState(const char* filename);
    void loadState(const char* filename);

private:
    CPU cpu;
    Memory memory;
    PPU ppu;
    APU apu;

    bool running;
    bool paused;
    int cycleCounter;

    static constexpr int CYCLES_PER_FRAME = 21477; // Approximate SNES cycles per frame

    void runCycle();
};

#endif // SNES_EMULATOR_H
