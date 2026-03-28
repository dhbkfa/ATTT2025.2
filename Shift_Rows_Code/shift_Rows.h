#ifndef SHIFT_ROWS_H
#define SHIFT_ROWS_H

#include <stdint.h>
#include <array>

using namespace std;

array<uint32_t, 4> shiftRows(array<uint32_t, 4> w);
array<uint32_t, 4> invShiftRows(array<uint32_t, 4> w);

#endif