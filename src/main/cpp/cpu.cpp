#include "include/cpu.h"
#include "include/memory.h"
#include <android/log.h>

#define TAG "SNESEmulator-CPU"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

CPU::CPU(Memory* mem)
    : memory(mem), A(0), X(0), Y(0), SP(0x1FF), PC(0x8000), P(0x34), DBR(0), PBR(0) {}

CPU::~CPU() = default;

void CPU::reset() {
    A = 0;
    X = 0;
    Y = 0;
    SP = 0x1FF;
    PC = 0x8000;
    P = 0x34;
    DBR = 0;
    PBR = 0;
    cycleCount = 0;
    instructionCount = 0;
}

void CPU::execute() {
    if (instructionCount % 10000 == 0) {
        LOGI("CPU: PC=%04X A=%04X X=%04X Y=%04X SP=%04X", PC, A, X, Y, SP);
    }
    fetchDecode();
    instructionCount++;
}

void CPU::fetchDecode() {
    uint8_t opcode = read8(PC);
    PC++;
    executeInstruction(opcode);
}

void CPU::executeInstruction(uint8_t opcode) {
    // Simplified opcode execution - implement most common ones
    switch (opcode) {
        case 0xA9: opLDA(addressImmediate()); break;  // LDA #imm
        case 0xAD: opLDA(addressAbsolute()); break;   // LDA abs
        case 0xBD: opLDA(addressAbsoluteX()); break;  // LDA abs,X
        case 0x8D: opSTA(addressAbsolute()); break;   // STA abs
        case 0x9D: opSTA(addressAbsoluteX()); break;  // STA abs,X
        case 0xA2: opLDX(addressImmediate()); break;  // LDX #imm
        case 0xAE: opLDX(addressAbsolute()); break;   // LDX abs
        case 0xA0: opLDY(addressImmediate()); break;  // LDY #imm
        case 0xAC: opLDY(addressAbsolute()); break;   // LDY abs
        case 0x69: opADC(addressImmediate()); break;  // ADC #imm
        case 0x6D: opADC(addressAbsolute()); break;   // ADC abs
        case 0xE9: opSBC(addressImmediate()); break;  // SBC #imm
        case 0xED: opSBC(addressAbsolute()); break;   // SBC abs
        case 0xC9: opCMP(addressImmediate()); break;  // CMP #imm
        case 0xCD: opCMP(addressAbsolute()); break;   // CMP abs
        case 0x29: opAND(addressImmediate()); break;  // AND #imm
        case 0x2D: opAND(addressAbsolute()); break;   // AND abs
        case 0x09: opORA(addressImmediate()); break;  // ORA #imm
        case 0x0D: opORA(addressAbsolute()); break;   // ORA abs
        case 0x49: opEOR(addressImmediate()); break;  // EOR #imm
        case 0x4D: opEOR(addressAbsolute()); break;   // EOR abs
        case 0x0A: opASL(addressAccumulator()); break;// ASL A
        case 0x4A: opLSR(addressAccumulator()); break;// LSR A
        case 0xEA: opNOP(); break;                     // NOP
        case 0x18: opCLC(); break;                     // CLC
        case 0x38: opSEC(); break;                     // SEC
        case 0x58: opCLI(); break;                     // CLI
        case 0x78: opSEI(); break;                     // SEI
        case 0xF8: opSED(); break;                     // SED
        case 0xD8: opCLD(); break;                     // CLD
        case 0xB8: opCLV(); break;                     // CLV
        case 0xE8: opINX(); break;                     // INX
        case 0xC8: opINY(); break;                     // INY
        case 0xCA: opDEX(); break;                     // DEX
        case 0x88: opDEY(); break;                     // DEY
        case 0xAA: opTAX(); break;                     // TAX
        case 0xA8: opTAY(); break;                     // TAY
        case 0x8A: opTXA(); break;                     // TXA
        case 0x98: opTYA(); break;                     // TYA
        case 0x80: opBRA((int8_t)read8(PC)); PC++; break; // BRA
        case 0xF0: opBEQ((int8_t)read8(PC)); PC++; break; // BEQ
        case 0xD0: opBNE((int8_t)read8(PC)); PC++; break; // BNE
        case 0xB0: opBCS((int8_t)read8(PC)); PC++; break; // BCS
        case 0x90: opBCC((int8_t)read8(PC)); PC++; break; // BCC
        case 0x30: opBMI((int8_t)read8(PC)); PC++; break; // BMI
        case 0x10: opBPL((int8_t)read8(PC)); PC++; break; // BPL
        case 0x70: opBVS((int8_t)read8(PC)); PC++; break; // BVS
        case 0x50: opBVC((int8_t)read8(PC)); PC++; break; // BVC
        case 0x4C: { uint16_t addr = read16(PC); PC += 2; opJMP(addr); } break; // JMP
        case 0x20: { uint16_t addr = read16(PC); PC += 2; opJSR(addr); } break; // JSR
        case 0x60: opRTS(); break;                     // RTS
        case 0x40: opRTI(); break;                     // RTI
        case 0x00: opBRK(); break;                     // BRK
        case 0x48: opPHA(); break;                     // PHA
        case 0x68: opPLA(); break;                     // PLA
        case 0x08: opPHP(); break;                     // PHP
        case 0x28: opPLP(); break;                     // PLP
        default:
            LOGI("Unknown opcode: %02X at %04X", opcode, PC - 1);
            break;
    }
}

uint16_t CPU::addressImplied() { return 0; }
uint16_t CPU::addressAccumulator() { return 0; }
uint16_t CPU::addressAbsolute() {
    uint16_t addr = read16(PC);
    PC += 2;
    return addr;
}
uint16_t CPU::addressAbsoluteX() {
    uint16_t addr = read16(PC) + X;
    PC += 2;
    return addr;
}
uint16_t CPU::addressAbsoluteY() {
    uint16_t addr = read16(PC) + Y;
    PC += 2;
    return addr;
}
uint16_t CPU::addressImmediate() {
    uint16_t addr = PC;
    PC++;
    return addr;
}

uint8_t CPU::read8(uint16_t addr) {
    return memory->read(addr);
}

void CPU::write8(uint16_t addr, uint8_t value) {
    memory->write(addr, value);
}

uint16_t CPU::read16(uint16_t addr) {
    uint8_t lo = read8(addr);
    uint8_t hi = read8(addr + 1);
    return (hi << 8) | lo;
}

void CPU::write16(uint16_t addr, uint16_t value) {
    write8(addr, value & 0xFF);
    write8(addr + 1, (value >> 8) & 0xFF);
}

void CPU::push8(uint8_t value) {
    write8(SP, value);
    SP--;
}

void CPU::push16(uint16_t value) {
    push8((value >> 8) & 0xFF);
    push8(value & 0xFF);
}

uint8_t CPU::pop8() {
    SP++;
    return read8(SP);
}

uint16_t CPU::pop16() {
    uint8_t lo = pop8();
    uint8_t hi = pop8();
    return (hi << 8) | lo;
}

void CPU::setZN(uint16_t value) {
    flagZ = (value == 0);
    flagN = (value & 0x8000) != 0;
}

// Instruction implementations
void CPU::opLDA(uint16_t addr) { A = read8(addr); setZN(A); }
void CPU::opLDX(uint16_t addr) { X = read8(addr); setZN(X); }
void CPU::opLDY(uint16_t addr) { Y = read8(addr); setZN(Y); }
void CPU::opSTA(uint16_t addr) { write8(addr, A); }
void CPU::opSTX(uint16_t addr) { write8(addr, X); }
void CPU::opSTY(uint16_t addr) { write8(addr, Y); }
void CPU::opADC(uint16_t addr) { uint16_t result = A + read8(addr) + (flagC ? 1 : 0); flagC = result > 0xFF; A = result & 0xFF; setZN(A); }
void CPU::opSBC(uint16_t addr) { uint16_t result = A - read8(addr) - (flagC ? 0 : 1); flagC = result < 0x100; A = result & 0xFF; setZN(A); }
void CPU::opCMP(uint16_t addr) { uint16_t result = A - read8(addr); setZN(result); flagC = result < 0x100; }
void CPU::opCPX(uint16_t addr) { uint16_t result = X - read8(addr); setZN(result); flagC = result < 0x100; }
void CPU::opCPY(uint16_t addr) { uint16_t result = Y - read8(addr); setZN(result); flagC = result < 0x100; }
void CPU::opAND(uint16_t addr) { A &= read8(addr); setZN(A); }
void CPU::opORA(uint16_t addr) { A |= read8(addr); setZN(A); }
void CPU::opEOR(uint16_t addr) { A ^= read8(addr); setZN(A); }
void CPU::opASL(uint16_t addr) { uint16_t val = A << 1; flagC = (val > 0xFF); A = val & 0xFF; setZN(A); }
void CPU::opLSR(uint16_t addr) { flagC = (A & 1) != 0; A >>= 1; setZN(A); }
void CPU::opINX() { X++; setZN(X); }
void CPU::opINY() { Y++; setZN(Y); }
void CPU::opDEX() { X--; setZN(X); }
void CPU::opDEY() { Y--; setZN(Y); }
void CPU::opTAX() { X = A; setZN(X); }
void CPU::opTAY() { Y = A; setZN(Y); }
void CPU::opTXA() { A = X; setZN(A); }
void CPU::opTYA() { A = Y; setZN(A); }
void CPU::opBRA(int8_t offset) { PC += offset; }
void CPU::opBEQ(int8_t offset) { if (flagZ) PC += offset; }
void CPU::opBNE(int8_t offset) { if (!flagZ) PC += offset; }
void CPU::opBCS(int8_t offset) { if (flagC) PC += offset; }
void CPU::opBCC(int8_t offset) { if (!flagC) PC += offset; }
void CPU::opBMI(int8_t offset) { if (flagN) PC += offset; }
void CPU::opBPL(int8_t offset) { if (!flagN) PC += offset; }
void CPU::opBVS(int8_t offset) { if (flagV) PC += offset; }
void CPU::opBVC(int8_t offset) { if (!flagV) PC += offset; }
void CPU::opJMP(uint16_t addr) { PC = addr; }
void CPU::opJSR(uint16_t addr) { push16(PC - 1); PC = addr; }
void CPU::opRTS() { PC = pop16() + 1; }
void CPU::opRTI() { P = pop8(); PC = pop16(); }
void CPU::opBRK() { push16(PC); push8(P | 0x10); PC = read16(0xFFFE); }
void CPU::opCLC() { flagC = false; }
void CPU::opSEC() { flagC = true; }
void CPU::opCLD() { flagD = false; }
void CPU::opSED() { flagD = true; }
void CPU::opCLI() { flagI = false; }
void CPU::opSEI() { flagI = true; }
void CPU::opCLV() { flagV = false; }
void CPU::opNOP() { /* No operation */ }
void CPU::opPHA() { push8(A); }
void CPU::opPHX() { push8(X); }
void CPU::opPHY() { push8(Y); }
void CPU::opPHP() { push8(P); }
void CPU::opPLA() { A = pop8(); setZN(A); }
void CPU::opPLX() { X = pop8(); setZN(X); }
void CPU::opPLY() { Y = pop8(); setZN(Y); }
void CPU::opPLP() { P = pop8(); }
void CPU::opBIT(uint16_t addr) { uint8_t val = read8(addr); flagZ = (A & val) == 0; flagN = (val & 0x80) != 0; flagV = (val & 0x40) != 0; }
void CPU::opINC(uint16_t addr) { uint8_t val = read8(addr) + 1; write8(addr, val); setZN(val); }
void CPU::opDEC(uint16_t addr) { uint8_t val = read8(addr) - 1; write8(addr, val); setZN(val); }
void CPU::opROL(uint16_t addr) { uint16_t val = (A << 1) | (flagC ? 1 : 0); flagC = (val > 0xFF); A = val & 0xFF; setZN(A); }
void CPU::opROR(uint16_t addr) { uint16_t val = A | ((flagC ? 1 : 0) << 8); flagC = (A & 1) != 0; A = val >> 1; setZN(A); }
void CPU::opAbsoluteIndirect() {}
void CPU::opAbsoluteIndexedIndirect() {}
void CPU::opDirect() {}
void CPU::opDirectX() {}
void CPU::opDirectY() {}
void CPU::opDirectIndirect() {}
void CPU::opDirectIndirectY() {}
void CPU::opProgCounter() {}
