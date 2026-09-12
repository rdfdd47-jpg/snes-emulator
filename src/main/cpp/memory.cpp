#include "include/memory.h"

Memory::Memory() : romSize(0) {
    reset();
}

Memory::~Memory() {}

void Memory::reset() {
    cpuRam.fill(0);
    vram.fill(0);
    oam.fill(0);
    cgram.fill(0);
    rom.fill(0);
    romSize = 0;
}

uint8_t Memory::readByte(uint32_t address) {
    address = mapAddress(address);

    // CPU RAM
    if (address < 0x020000) {
        return cpuRam[address];
    }
    // ROM
    else if (address >= 0x800000 && address < 0x800000 + romSize) {
        return rom[address - 0x800000];
    }
    // TODO: Add PPU, APU, and other memory-mapped I/O

    return 0;
}

uint16_t Memory::readWord(uint32_t address) {
    uint8_t low = readByte(address);
    uint8_t high = readByte(address + 1);
    return (high << 8) | low;
}

void Memory::writeByte(uint32_t address, uint8_t value) {
    address = mapAddress(address);

    // CPU RAM
    if (address < 0x020000) {
        cpuRam[address] = value;
    }
    // TODO: Add PPU, APU, and other memory-mapped I/O
}

void Memory::writeWord(uint32_t address, uint16_t value) {
    writeByte(address, value & 0xFF);
    writeByte(address + 1, (value >> 8) & 0xFF);
}

void Memory::loadROM(const uint8_t* romData, size_t size) {
    romSize = (size > 0x400000) ? 0x400000 : size;
    for (size_t i = 0; i < romSize; i++) {
        rom[i] = romData[i];
    }
}

uint32_t Memory::mapAddress(uint32_t address) {
    // TODO: Implement proper SNES address mapping
    // Handle bank switching and address mirroring
    return address;
}
