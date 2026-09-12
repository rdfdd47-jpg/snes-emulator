#include "include/ppu.h"
#include "include/memory.h"
#include <cstring>
#include <android/log.h>

#define TAG "SNESEmulator-PPU"

PPU::PPU(Memory* mem)
    : memory(mem), scanline(0), dotCycle(0) {}

PPU::~PPU() = default;

void PPU::update() {
    // SNES: 1364 dots per scanline, 262 scanlines
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
    if (!frameBuffer) return;

    // SNES native resolution: 256x224
    // Fill with a simple test pattern for now
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = y * width + x;
            // Simple gradient pattern to verify rendering
            uint8_t r = (x * 255) / width;
            uint8_t g = (y * 255) / height;
            uint8_t b = 128;
            uint8_t a = 0xFF;
            frameBuffer[idx] = (a << 24) | (b << 16) | (g << 8) | r;
        }
    }
}
