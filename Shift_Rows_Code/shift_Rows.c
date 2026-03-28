#include "shift_Rows.h"

void shiftRows(uint8_t state[4][4]) {
    uint8_t temp;
    // Hàng 1: dịch trái 1 byte
    temp        = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;
    // Hàng 2: dịch trái 2 byte
    temp        = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp        = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
    // Hàng 3: dịch trái 3 byte ~ dịch phải 1 byte
    temp        = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

void invShiftRows(uint8_t state[4][4]) {
    uint8_t temp;
    // Hàng 1: dịch phải 1 byte
    temp        = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp;
    // Hàng 2: dịch phải 2 byte ~ dich trái 2 byte
    temp        = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp        = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
    // Hàng 3: dịch phải 3 byte ~ dịch trái 1 byte
    temp        = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}