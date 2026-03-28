#include "shift_Rows.h"

uint32_t* shiftRows(uint32_t w[4]) {
    uint32_t tmp[4];
    tmp[0] = (w[0] & 0xFF000000) | (w[1] & 0x00FF0000) | (w[2] & 0x0000FF00) | (w[3] & 0x000000FF);
    tmp[1] = (w[1] & 0xFF000000) | (w[2] & 0x00FF0000) | (w[3] & 0x0000FF00) | (w[0] & 0x000000FF);
    tmp[2] = (w[2] & 0xFF000000) | (w[3] & 0x00FF0000) | (w[0] & 0x0000FF00) | (w[1] & 0x000000FF);
    tmp[3] = (w[3] & 0xFF000000) | (w[0] & 0x00FF0000) | (w[1] & 0x0000FF00) | (w[2] & 0x000000FF);
    w[0] = tmp[0]; w[1] = tmp[1]; w[2] = tmp[2]; w[3] = tmp[3];
    return w;
}

uint32_t* invShiftRows(uint32_t w[4]) {
    uint32_t tmp[4];
    tmp[0] = (w[0] & 0xFF000000) | (w[3] & 0x00FF0000) | (w[2] & 0x0000FF00) | (w[1] & 0x000000FF);
    tmp[1] = (w[1] & 0xFF000000) | (w[0] & 0x00FF0000) | (w[3] & 0x0000FF00) | (w[2] & 0x000000FF);
    tmp[2] = (w[2] & 0xFF000000) | (w[1] & 0x00FF0000) | (w[0] & 0x0000FF00) | (w[3] & 0x000000FF);
    tmp[3] = (w[3] & 0xFF000000) | (w[2] & 0x00FF0000) | (w[1] & 0x0000FF00) | (w[0] & 0x000000FF);
    w[0] = tmp[0]; w[1] = tmp[1]; w[2] = tmp[2]; w[3] = tmp[3];
    return w;
}