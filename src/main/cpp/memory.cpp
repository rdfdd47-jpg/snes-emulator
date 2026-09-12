#include "include/memory.h"
#include "include/cartridge.h"

Memory::Memory() : cartridge(nullptr) {
    ram.resize(128 * 1024, 0); // 128KB RAM
    vram.resize(64 * 1024, 0); // 64KB VRAM
    cgram.resize(512, 0);       // 512 bytes CGRAM
}

Memory::~Memory() = default;

uint8_t Memory::read(uint32_t addr) {
    // TODO: Implement full address space mapping
    if (addr < 0x20000) {
        return ram[addr & 0x1FFFF];
    }
    return 0;
}

void Memory::write(uint32_t addr, uint8_t value) {
    // TODO: Implement full address space mapping
    if (addr < 0x20000) {
        ram[addr & 0x1FFFF] = value;
    }
}

void Memory::loadCartridge(Cartridge* cart) {
    cartridge = cart;
}

void Memory::reset() {
    std::fill(ram.begin(), ram.end(), 0);
    std::fill(vram.begin(), vram.end(), 0);
    std::fill(cgram.begin(), cgram.end(), 0);
}

void Memory::setInput(uint32_t button, bool pressed) {
    // TODO: Implement input handling
}
