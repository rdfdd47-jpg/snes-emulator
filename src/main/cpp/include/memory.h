#pragma once

#include <cstdint>
#include <vector>

class Cartridge;

class Memory {
public:
    Memory();
    ~Memory();

    uint8_t read(uint32_t addr);
    void write(uint32_t addr, uint8_t value);

    void loadCartridge(Cartridge* cart);
    void reset();
    void setInput(uint32_t button, bool pressed);

private:
    std::vector<uint8_t> ram; // 128KB internal RAM
    std::vector<uint8_t> vram; // Video RAM
    std::vector<uint8_t> cgram; // Color RAM
    Cartridge* cartridge;
};
