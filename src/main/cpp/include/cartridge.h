#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Cartridge {
public:
    Cartridge();
    ~Cartridge();

    bool loadROM(const std::string& path);
    void unloadROM();

    uint8_t read(uint32_t addr) const;
    bool isLoaded() const { return loaded; }

private:
    std::vector<uint8_t> romData;
    bool loaded;
};
