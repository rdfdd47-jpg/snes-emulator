#include "include/cartridge.h"
#include <fstream>
#include <android/log.h>

#define TAG "SNESEmulator"

Cartridge::Cartridge() : loaded(false) {}

Cartridge::~Cartridge() {
    unloadROM();
}

bool Cartridge::loadROM(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to open ROM: %s", path.c_str());
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    romData.resize(size);
    if (!file.read(reinterpret_cast<char*>(romData.data()), size)) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to read ROM");
        return false;
    }

    loaded = true;
    __android_log_print(ANDROID_LOG_INFO, TAG, "ROM loaded successfully: %ld bytes", size);
    return true;
}

void Cartridge::unloadROM() {
    romData.clear();
    loaded = false;
}

uint8_t Cartridge::read(uint32_t addr) const {
    if (addr < romData.size()) {
        return romData[addr];
    }
    return 0;
}
