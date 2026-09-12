#ifndef SNES_MEMORY_H
#define SNES_MEMORY_H

#include <cstdint>
#include <array>

class Memory {
public:
    static constexpr size_t RAM_SIZE = 0x20000;      // 128 KB
    static constexpr size_t VRAM_SIZE = 0x10000;     // 64 KB
    static constexpr size_t OAM_SIZE = 0x200;        // 512 bytes
    static constexpr size_t CGRAM_SIZE = 0x200;      // 512 bytes (color palette)

    Memory();
    ~Memory();

    // Read operations
    uint8_t readByte(uint32_t address);
    uint16_t readWord(uint32_t address);

    // Write operations
    void writeByte(uint32_t address, uint8_t value);
    void writeWord(uint32_t address, uint16_t value);

    // ROM operations
    void loadROM(const uint8_t* romData, size_t romSize);

    // Reset memory
    void reset();

private:
    std::array<uint8_t, RAM_SIZE> cpuRam;
    std::array<uint8_t, VRAM_SIZE> vram;
    std::array<uint8_t, OAM_SIZE> oam;
    std::array<uint8_t, CGRAM_SIZE> cgram;
    std::array<uint8_t, 0x400000> rom;  // Up to 4 MB cartridge
    size_t romSize;

    // Helper for address mapping
    uint32_t mapAddress(uint32_t address);
};

#endif // SNES_MEMORY_H
