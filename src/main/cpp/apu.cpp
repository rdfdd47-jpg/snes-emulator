#include "include/apu.h"
#include "include/memory.h"

APU::APU(Memory* mem) : memory(mem) {}

APU::~APU() = default;

void APU::update() {
    // TODO: Implement audio processing
}

void APU::reset() {
    // TODO: Reset audio state
}
