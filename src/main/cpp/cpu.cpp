#include "include/cpu.h"
#include "include/memory.h"

CPU::CPU(Memory* mem)
    : memory(mem), A(0), X(0), Y(0), SP(0x1FF), PC(0x8000), P(0x34) {}

CPU::~CPU() = default;

void CPU::reset() {
    A = 0;
    X = 0;
    Y = 0;
    SP = 0x1FF;
    PC = 0x8000;
    P = 0x34;
}

void CPU::execute() {
    // Fetch and decode instruction
    fetchDecode();
}

void CPU::fetchDecode() {
    // TODO: Implement full 65C816 instruction set
    // This is a placeholder for the CPU execution loop
    PC++;
}

void CPU::executeInstruction(uint8_t opcode) {
    // TODO: Implement instruction execution based on opcode
}
