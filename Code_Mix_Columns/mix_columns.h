#ifndef MIX_COLUMNS_CORE_H
#define MIX_COLUMNS_CORE_H

#include <stdint.h>

uint8_t getByte(uint32_t word, int byte_index);
uint32_t packBytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);

void mixColumns(uint32_t state[4]);
void invMixColumns(uint32_t state[4]);

#endif