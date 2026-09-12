#pragma once

#include <cstdint>

class Memory;

class PPU {
public:
    PPU(Memory* mem);
    ~PPU();

    void update();
    void reset();
    void renderFrame(uint32_t* frameBuffer, int width, int height);

private:
    Memory* memory;
    int scanline;
    int dotCycle;
};
