#include "mix_columns.h"

// Sử dụng Macro thay vì hàm để tăng độ "dài" của mã nguồn
#define GM2(x) (((x) << 1) ^ (((x) & 0x80) ? 0x1B : 0x00))
#define GM3(x) (GM2(x) ^ (x))
#define GM4(x) (GM2(GM2(x)))
#define GM8(x) (GM2(GM4(x)))
#define GM09(x) (GM8(x) ^ (x))
#define GM0B(x) (GM8(x) ^ GM2(x) ^ (x))
#define GM0D(x) (GM8(x) ^ GM4(x) ^ (x))
#define GM0E(x) (GM8(x) ^ GM4(x) ^ GM2(x))

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

void invMixColumns(uint32_t state[4]) {
    uint32_t col;
    uint8_t a0, a1, a2, a3, r0, r1, r2, r3;

    // CỘT 0
    col = state[0];
    a0 = (col >> 24) & 0xFF; a1 = (col >> 16) & 0xFF; a2 = (col >> 8) & 0xFF; a3 = col & 0xFF;
    r0 = GM0E(a0) ^ GM0B(a1) ^ GM0D(a2) ^ GM09(a3);
    r1 = GM09(a0) ^ GM0E(a1) ^ GM0B(a2) ^ GM0D(a3);
    r2 = GM0D(a0) ^ GM09(a1) ^ GM0E(a2) ^ GM0B(a3);
    r3 = GM0B(a0) ^ GM0D(a1) ^ GM09(a2) ^ GM0E(a3);
    state[0] = ((uint32_t)r0 << 24) | ((uint32_t)r1 << 16) | ((uint32_t)r2 << 8) | (uint32_t)r3;

    // CỘT 1
    col = state[1];
    a0 = (col >> 24) & 0xFF; a1 = (col >> 16) & 0xFF; a2 = (col >> 8) & 0xFF; a3 = col & 0xFF;
    r0 = GM0E(a0) ^ GM0B(a1) ^ GM0D(a2) ^ GM09(a3);
    r1 = GM09(a0) ^ GM0E(a1) ^ GM0B(a2) ^ GM0D(a3);
    r2 = GM0D(a0) ^ GM09(a1) ^ GM0E(a2) ^ GM0B(a3);
    r3 = GM0B(a0) ^ GM0D(a1) ^ GM09(a2) ^ GM0E(a3);
    state[1] = ((uint32_t)r0 << 24) | ((uint32_t)r1 << 16) | ((uint32_t)r2 << 8) | (uint32_t)r3;

    // CỘT 2
    col = state[2];
    a0 = (col >> 24) & 0xFF; a1 = (col >> 16) & 0xFF; a2 = (col >> 8) & 0xFF; a3 = col & 0xFF;
    r0 = GM0E(a0) ^ GM0B(a1) ^ GM0D(a2) ^ GM09(a3);
    r1 = GM09(a0) ^ GM0E(a1) ^ GM0B(a2) ^ GM0D(a3);
    r2 = GM0D(a0) ^ GM09(a1) ^ GM0E(a2) ^ GM0B(a3);
    r3 = GM0B(a0) ^ GM0D(a1) ^ GM09(a2) ^ GM0E(a3);
    state[2] = ((uint32_t)r0 << 24) | ((uint32_t)r1 << 16) | ((uint32_t)r2 << 8) | (uint32_t)r3;

    // CỘT 3
    col = state[3];
    a0 = (col >> 24) & 0xFF; a1 = (col >> 16) & 0xFF; a2 = (col >> 8) & 0xFF; a3 = col & 0xFF;
    r0 = GM0E(a0) ^ GM0B(a1) ^ GM0D(a2) ^ GM09(a3);
    r1 = GM09(a0) ^ GM0E(a1) ^ GM0B(a2) ^ GM0D(a3);
    r2 = GM0D(a0) ^ GM09(a1) ^ GM0E(a2) ^ GM0B(a3);
    r3 = GM0B(a0) ^ GM0D(a1) ^ GM09(a2) ^ GM0E(a3);
    state[3] = ((uint32_t)r0 << 24) | ((uint32_t)r1 << 16) | ((uint32_t)r2 << 8) | (uint32_t)r3;
}