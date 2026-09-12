#include "../include/snes_emulator.h"
#include "../include/cpu.h"
#include "../include/memory.h"
#include "../include/ppu.h"
#include "../include/apu.h"
#include "../include/cartridge.h"

SNESEmulator::SNESEmulator()
    : running(false), romLoaded(false), cycleCount(0) {
    // Initialize components
    memory = std::make_unique<Memory>();
    cpu = std::make_unique<CPU>(memory.get());
    ppu = std::make_unique<PPU>(memory.get());
    apu = std::make_unique<APU>(memory.get());
    cartridge = std::make_unique<Cartridge>();
}

SNESEmulator::~SNESEmulator() = default;

bool SNESEmulator::loadROM(const std::string& romPath) {
    if (!cartridge->loadROM(romPath)) {
        return false;
    }
    romLoaded = true;
    memory->loadCartridge(cartridge.get());
    return true;
}

void SNESEmulator::unloadROM() {
    cartridge->unloadROM();
    romLoaded = false;
    running = false;
}

void SNESEmulator::run() {
    if (romLoaded) {
        running = true;
    }
}

void SNESEmulator::pause() {
    running = false;
}

void SNESEmulator::reset() {
    cpu->reset();
    memory->reset();
    ppu->reset();
    apu->reset();
    cycleCount = 0;
}

void SNESEmulator::step() {
    if (running && romLoaded) {
        // Execute CPU cycle
        cpu->execute();
        cycleCount++;

        // Update graphics every 4 cycles (rough approximation)
        if (cycleCount % 4 == 0) {
            ppu->update();
        }

        // Update audio
        apu->update();
    }
}

void SNESEmulator::renderFrame(uint32_t* frameBuffer, int width, int height) {
    if (ppu) {
        ppu->renderFrame(frameBuffer, width, height);
    }
}

void SNESEmulator::handleInput(uint32_t button, bool pressed) {
    memory->setInput(button, pressed);
}
