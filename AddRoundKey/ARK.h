#ifndef ARK_H
#define ARK_H

#include <stdint.h>

void AddRoundKey(uint32_t state[4], const uint32_t roundKey[4]);

#endif // ARK_H
