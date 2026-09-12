#include "include/emulator.h"

Emulator::Emulator() : running(false), paused(false), cycleCounter(0) {}

Emulator::~Emulator() {}

void Emulator::init() {
    cpu.init();
    memory.reset();
    ppu.init();
    apu.init();
    running = true;
    cycleCounter = 0;
}

bool Emulator::loadROM(const uint8_t* romData, size_t romSize) {
    if (!romData || romSize == 0) {
        return false;
    }
    memory.loadROM(romData, romSize);
    return true;
}

void Emulator::runFrame() {
    if (!running || paused) {
        return;
    }

    cycleCounter = 0;
    while (cycleCounter < CYCLES_PER_FRAME) {
        runCycle();
    }

    ppu.renderFrame();
    apu.generateSamples(SAMPLE_RATE / 60); // 60 FPS
}

void Emulator::runCycle() {
    cpu.step();
    cycleCounter++;

    // PPU runs at 3x CPU speed (approximately)
    if (cycleCounter % 3 == 0) {
        ppu.step();
    }

    // APU runs independently
    apu.step();
}

void Emulator::reset() {
    init();
}

void Emulator::pause() {
    paused = true;
}

void Emulator::resume() {
    paused = false;
}

bool Emulator::isRunning() const {
    return running && !paused;
}

const uint32_t* Emulator::getFramebuffer() const {
    return ppu.getFramebuffer();
}

const int16_t* Emulator::getAudioBuffer() const {
    return apu.getAudioBuffer();
}

int Emulator::getAvailableSamples() const {
    return apu.getAvailableSamples();
}

void Emulator::saveState(const char* filename) {
    // TODO: Implement state saving
}

void Emulator::loadState(const char* filename) {
    // TODO: Implement state loading
}
