#include "include/ppu.h"
#include "include/memory.h"

PPU::PPU(Memory* mem)
    : memory(mem), scanline(0), dotCycle(0) {}

PPU::~PPU() = default;

void PPU::update() {
    // Update scanline and dot cycle
    dotCycle++;
    if (dotCycle >= 1364) {
        dotCycle = 0;
        scanline++;
        if (scanline >= 262) {
            scanline = 0;
        }
    }
}

void PPU::reset() {
    scanline = 0;
    dotCycle = 0;
}

void PPU::renderFrame(uint32_t* frameBuffer, int width, int height) {
    // TODO: Implement frame rendering
    // For now, fill with black
    if (frameBuffer) {
        for (int i = 0; i < width * height; i++) {
            frameBuffer[i] = 0xFF000000; // Black with full alpha
        }
    }
}
