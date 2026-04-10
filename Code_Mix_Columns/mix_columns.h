#ifndef MIX_COLUMNS_H
#define MIX_COLUMNS_H

#include <stdint.h>

void mixColumns(uint32_t state[4]);
void invMixColumns(uint32_t state[4]);

#endif // MIX_COLUMNS_H
