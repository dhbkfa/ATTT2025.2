#include "shift_Rows.h"

using namespace std;

array<uint32_t, 4> shiftRows(array<uint32_t, 4> w) {
    return {{
        (w[0] & 0xFF000000) | (w[1] & 0x00FF0000) | (w[2] & 0x0000FF00) | (w[3] & 0x000000FF),
        (w[1] & 0xFF000000) | (w[2] & 0x00FF0000) | (w[3] & 0x0000FF00) | (w[0] & 0x000000FF),
        (w[2] & 0xFF000000) | (w[3] & 0x00FF0000) | (w[0] & 0x0000FF00) | (w[1] & 0x000000FF),
        (w[3] & 0xFF000000) | (w[0] & 0x00FF0000) | (w[1] & 0x0000FF00) | (w[2] & 0x000000FF)
    }};
}

array<uint32_t, 4> invShiftRows(array<uint32_t, 4> w) {
    return {{
        (w[0] & 0xFF000000) | (w[3] & 0x00FF0000) | (w[2] & 0x0000FF00) | (w[1] & 0x000000FF),
        (w[1] & 0xFF000000) | (w[0] & 0x00FF0000) | (w[3] & 0x0000FF00) | (w[2] & 0x000000FF),
        (w[2] & 0xFF000000) | (w[1] & 0x00FF0000) | (w[0] & 0x0000FF00) | (w[3] & 0x000000FF),
        (w[3] & 0xFF000000) | (w[2] & 0x00FF0000) | (w[1] & 0x0000FF00) | (w[0] & 0x000000FF)
    }};
}