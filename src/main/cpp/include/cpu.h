#pragma once

#include <cstdint>
#include <array>

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
    uint8_t DBR; // Data Bank Register
    uint8_t PBR; // Program Bank Register

    // Flags
    bool flagN = false; // Negative
    bool flagV = false; // Overflow
    bool flagM = false; // Accumulator width
    bool flagX = false; // Index width
    bool flagD = false; // Decimal mode
    bool flagI = false; // Interrupt disable
    bool flagZ = false; // Zero
    bool flagC = false; // Carry

    uint64_t cycleCount = 0;
    uint64_t instructionCount = 0;

    void fetchDecode();
    void executeInstruction(uint8_t opcode);
    
    // Addressing modes
    uint16_t addressImplied();
    uint16_t addressAccumulator();
    uint16_t addressAbsolute();
    uint16_t addressAbsoluteX();
    uint16_t addressAbsoluteY();
    uint16_t addressAbsoluteIndirect();
    uint16_t addressAbsoluteIndexedIndirect();
    uint16_t addressDirect();
    uint16_t addressDirectX();
    uint16_t addressDirectY();
    uint16_t addressDirectIndirect();
    uint16_t addressDirectIndirectY();
    uint16_t addressProgCounter();
    uint16_t addressImmediate();

    // Instructions
    void opLDA(uint16_t addr);
    void opLDX(uint16_t addr);
    void opLDY(uint16_t addr);
    void opSTA(uint16_t addr);
    void opSTX(uint16_t addr);
    void opSTY(uint16_t addr);
    void opADC(uint16_t addr);
    void opSBC(uint16_t addr);
    void opCMP(uint16_t addr);
    void opCPX(uint16_t addr);
    void opCPY(uint16_t addr);
    void opAND(uint16_t addr);
    void opORA(uint16_t addr);
    void opEOR(uint16_t addr);
    void opASL(uint16_t addr);
    void opLSR(uint16_t addr);
    void opROL(uint16_t addr);
    void opROR(uint16_t addr);
    void opBIT(uint16_t addr);
    void opINC(uint16_t addr);
    void opDEC(uint16_t addr);
    void opINX();
    void opINY();
    void opDEX();
    void opDEY();
    void opTAX();
    void opTAY();
    void opTXA();
    void opTYA();
    void opBRA(int8_t offset);
    void opBEQ(int8_t offset);
    void opBNE(int8_t offset);
    void opBCS(int8_t offset);
    void opBCC(int8_t offset);
    void opBMI(int8_t offset);
    void opBPL(int8_t offset);
    void opBVS(int8_t offset);
    void opBVC(int8_t offset);
    void opJMP(uint16_t addr);
    void opJSR(uint16_t addr);
    void opRTS();
    void opRTI();
    void opBRK();
    void opCLC();
    void opSEC();
    void opCLD();
    void opSED();
    void opCLI();
    void opSEI();
    void opCLV();
    void opNOP();
    void opPHA();
    void opPHX();
    void opPHY();
    void opPHP();
    void opPLA();
    void opPLX();
    void opPLY();
    void opPLP();

    uint8_t read8(uint16_t addr);
    void write8(uint16_t addr, uint8_t value);
    uint16_t read16(uint16_t addr);
    void write16(uint16_t addr, uint16_t value);
    void push8(uint8_t value);
    void push16(uint16_t value);
    uint8_t pop8();
    uint16_t pop16();
    void updateFlags(uint16_t result);
    void setZN(uint16_t value);
};
