#ifndef SUBBYTES_H
#define SUBBYTES_H

#include <stdint.h>

uint32_t subword(uint32_t word);
void subBytes(uint32_t state[4]);
void invSubBytes(uint32_t state[4]);

#endif // SUBBYTES_H
