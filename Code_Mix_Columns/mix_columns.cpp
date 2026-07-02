#include "mix_columns.h"

// ---------------------------------------------------------
// Các hàm trợ giúp nhân trên trường Galois (Galois Field)
// ---------------------------------------------------------
constexpr uint8_t gm2(uint8_t x) 
{ 
    return (x << 1) ^ ((x & 0x80) ? 0x1b : 0x00); 
}

constexpr uint8_t gm3(uint8_t x) 
{ 
    return gm2(x) ^ x; 
}

constexpr uint8_t gm4(uint8_t x) 
{ 
    return gm2(gm2(x)); 
}

constexpr uint8_t gm8(uint8_t x) 
{ 
    return gm2(gm4(x)); 
}

constexpr uint8_t gm09(uint8_t x) 
{ 
    return gm8(x) ^ x; 
}

constexpr uint8_t gm0b(uint8_t x) 
{ 
    return gm8(x) ^ gm2(x) ^ x; 
}

constexpr uint8_t gm0d(uint8_t x) 
{ 
    return gm8(x) ^ gm4(x) ^ x; 
}

constexpr uint8_t gm0e(uint8_t x) 
{ 
    return gm8(x) ^ gm4(x) ^ gm2(x); 
}



void mixColumns(uint32_t state[4]) {
    uint32_t col;
    uint8_t a0, a1, a2, a3, r0, r1, r2, r3;

    // CỘT 0
    col = state[0];
    a0 = (col >> 24) & 0xFF; a1 = (col >> 16) & 0xFF; a2 = (col >> 8) & 0xFF; a3 = col & 0xFF;
    r0 = GM2(a0) ^ GM3(a1) ^ a2 ^ a3;
    r1 = a0 ^ GM2(a1) ^ GM3(a2) ^ a3;
    r2 = a0 ^ a1 ^ GM2(a2) ^ GM3(a3);
    r3 = GM3(a0) ^ a1 ^ a2 ^ GM2(a3);
    state[0] = ((uint32_t)r0 << 24) | ((uint32_t)r1 << 16) | ((uint32_t)r2 << 8) | (uint32_t)r3;

    // CỘT 1
    col = state[1];
    a0 = (col >> 24) & 0xFF; a1 = (col >> 16) & 0xFF; a2 = (col >> 8) & 0xFF; a3 = col & 0xFF;
    r0 = GM2(a0) ^ GM3(a1) ^ a2 ^ a3;
    r1 = a0 ^ GM2(a1) ^ GM3(a2) ^ a3;
    r2 = a0 ^ a1 ^ GM2(a2) ^ GM3(a3);
    r3 = GM3(a0) ^ a1 ^ a2 ^ GM2(a3);
    state[1] = ((uint32_t)r0 << 24) | ((uint32_t)r1 << 16) | ((uint32_t)r2 << 8) | (uint32_t)r3;

    // CỘT 2
    col = state[2];
    a0 = (col >> 24) & 0xFF; a1 = (col >> 16) & 0xFF; a2 = (col >> 8) & 0xFF; a3 = col & 0xFF;
    r0 = GM2(a0) ^ GM3(a1) ^ a2 ^ a3;
    r1 = a0 ^ GM2(a1) ^ GM3(a2) ^ a3;
    r2 = a0 ^ a1 ^ GM2(a2) ^ GM3(a3);
    r3 = GM3(a0) ^ a1 ^ a2 ^ GM2(a3);
    state[2] = ((uint32_t)r0 << 24) | ((uint32_t)r1 << 16) | ((uint32_t)r2 << 8) | (uint32_t)r3;

    // CỘT 3
    col = state[3];
    a0 = (col >> 24) & 0xFF; a1 = (col >> 16) & 0xFF; a2 = (col >> 8) & 0xFF; a3 = col & 0xFF;
    r0 = GM2(a0) ^ GM3(a1) ^ a2 ^ a3;
    r1 = a0 ^ GM2(a1) ^ GM3(a2) ^ a3;
    r2 = a0 ^ a1 ^ GM2(a2) ^ GM3(a3);
    r3 = GM3(a0) ^ a1 ^ a2 ^ GM2(a3);
    state[3] = ((uint32_t)r0 << 24) | ((uint32_t)r1 << 16) | ((uint32_t)r2 << 8) | (uint32_t)r3;
}
// Làm tương tự cho InvMixColumns, mã sẽ rất dài.