#include "include/ppu.h"

PPU::PPU() : currentLine(0), currentColumn(0) {
    reset();
}

PPU::~PPU() {}

void PPU::init() {
    reset();
}

void PPU::reset() {
    framebuffer.fill(0);
    currentLine = 0;
    currentColumn = 0;
}

void PPU::step() {
    currentColumn++;
    if (currentColumn >= SCREEN_WIDTH) {
        currentColumn = 0;
        currentLine++;
        if (currentLine >= SCREEN_HEIGHT) {
            currentLine = 0;
        }
    }
}

void PPU::renderScanline(uint16_t scanline) {
    // TODO: Implement scanline rendering
    // Render backgrounds and sprites for this line
}

void PPU::renderFrame() {
    // TODO: Implement full frame rendering
    framebuffer.fill(0x000000FF); // Clear to black
    
    for (uint16_t i = 0; i < SCREEN_HEIGHT; i++) {
        renderScanline(i);
    }
}

const uint32_t* PPU::getFramebuffer() const {
    return framebuffer.data();
}

void PPU::renderBG(uint8_t bgNumber) {
    // TODO: Implement background rendering
}

void PPU::renderSprites() {
    // TODO: Implement sprite rendering
}

void PPU::compositePixel(int x, int y) {
    // TODO: Implement pixel composition from layers
}
