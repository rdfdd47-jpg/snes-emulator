#pragma once

#include <cstdint>

class Memory;

class CPU {
public:
    CPU(Memory* mem);
    ~CPU();

    void execute();
    void reset();

private:
    Memory* memory;

    // CPU Registers (WDC 65C816 - 16-bit processor)
    uint16_t A;  // Accumulator
    uint16_t X;  // X Index
    uint16_t Y;  // Y Index
    uint16_t SP; // Stack Pointer
    uint16_t PC; // Program Counter
    uint8_t P;   // Processor Status (flags)

    void fetchDecode();
    void executeInstruction(uint8_t opcode);
};
