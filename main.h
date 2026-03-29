#ifndef MAIN_H
#define MAIN_H
#include <stdint.h>

uint32_t subword(uint32_t word);
void subBytes(uint32_t state[4]);
void invSubBytes(uint32_t state[4]);
void shiftRows(uint32_t w[4]);
void invShiftRows(uint32_t w[4]);
void mixColumns(uint32_t state[4]);
void invMixColumns(uint32_t state[4]);
void AddRoundKey(uint32_t key[4],int i);
#endif








