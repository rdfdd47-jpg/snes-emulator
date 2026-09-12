#pragma once

#include <cstdint>

class Memory;

class APU {
public:
    APU(Memory* mem);
    ~APU();

    void update();
    void reset();

private:
    Memory* memory;
};
