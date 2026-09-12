#ifndef SNES_PPU_H
#define SNES_PPU_H

#include <cstdint>
#include <array>

class PPU {
public:
    static constexpr int SCREEN_WIDTH = 256;
    static constexpr int SCREEN_HEIGHT = 224;
    static constexpr int FRAMEBUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT * 4; // RGBA

    PPU();
    ~PPU();

    // Initialize PPU
    void init();

    // Render one scanline
    void renderScanline(uint16_t scanline);

    // Render complete frame
    void renderFrame();

    // Get the current framebuffer
    const uint32_t* getFramebuffer() const;

    // PPU cycle step
    void step();

    // Reset PPU
    void reset();

private:
    std::array<uint32_t, FRAMEBUFFER_SIZE / 4> framebuffer;
    uint16_t currentLine;
    uint16_t currentColumn;

    // Rendering helper functions
    void renderBG(uint8_t bgNumber);
    void renderSprites();
    void compositePixel(int x, int y);
};

#endif // SNES_PPU_H
