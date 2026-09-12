#include <cstdint>
#include <cstring>

struct ROMHeader {
    uint8_t makerCode[2];
    uint8_t gameCode[4];
    uint8_t reserved[7];
    uint8_t expansionRamSize;
    uint8_t specialVersion;
    uint8_t cartridgeType;
    uint8_t romSize;
    uint8_t ramSize;
    uint8_t destinationCode;
    uint8_t fixedValue;
    uint8_t version;
    uint16_t checksumComplement;
    uint16_t checksum;
};

bool validateROMHeader(const uint8_t* romData, size_t romSize) {
    if (romSize < 0x8000) {
        return false;
    }

    // Check for SNES header at offset 0x7FC0
    const ROMHeader* header = reinterpret_cast<const ROMHeader*>(romData + 0x7FC0);

    // Verify fixed value
    if (header->fixedValue != 0x00) {
        return false;
    }

    // TODO: Add checksum validation

    return true;
}

uint32_t getROMSize(const uint8_t* romData, size_t romSize) {
    if (romSize < 0x8000) {
        return 0;
    }

    const ROMHeader* header = reinterpret_cast<const ROMHeader*>(romData + 0x7FC0);
    
    // Calculate ROM size: 2^(romSizeValue + 10) bytes
    uint32_t size = 1 << (header->romSize + 10);
    
    return (size > romSize) ? romSize : size;
}

const char* getGameTitle(const uint8_t* romData, size_t romSize) {
    if (romSize < 0x8000) {
        return nullptr;
    }

    // Game title is at offset 0x7FC0 + 16 in the header
    static char title[22];
    memcpy(title, romData + 0x7FC0 + 16, 21);
    title[21] = '\0';

    return title;
}
