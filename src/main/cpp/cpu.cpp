#include "include/cpu.h"

CPU::CPU() : currentOpcode(0), cycleCounter(0) {
    reset();
}

CPU::~CPU() {}

void CPU::init() {
    reset();
}

void CPU::reset() {
    registers.pc = 0x8000;  // SNES start address
    registers.sp = 0x01FF;  // Stack at top of page 1
    registers.a = 0x00;
    registers.x = 0x00;
    registers.y = 0x00;
    registers.p = 0x34;     // Status flags
    registers.db = 0x00;
    cycleCounter = 0;
}

void CPU::step() {
    // Fetch opcode from memory
    // Decode and execute instruction
    // Update cycle counter
    cycleCounter++;
}

void CPU::execute(int cycles) {
    for (int i = 0; i < cycles; i++) {
        step();
    }
}

uint8_t CPU::getFlag(StatusFlags flag) {
    return (registers.p & flag) ? 1 : 0;
}

void CPU::setFlag(StatusFlags flag, bool value) {
    if (value) {
        registers.p |= flag;
    } else {
        registers.p &= ~flag;
    }
}

void CPU::executeInstruction(uint8_t opcode) {
    currentOpcode = opcode;
    // TODO: Implement full 65816 instruction set
    switch (opcode) {
        // Common opcodes
        default:
            break;
    }
}

void CPU::handleADC(uint16_t address) {
    // TODO: Implement ADC (Add with Carry)
}

void CPU::handleLDA(uint16_t address) {
    // TODO: Implement LDA (Load Accumulator)
}

void CPU::handleSTA(uint16_t address) {
    // TODO: Implement STA (Store Accumulator)
}
