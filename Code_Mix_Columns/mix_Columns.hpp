#ifndef MIX_COLUMNS_HPP
#define MIX_COLUMNS_HPP

#include <cstdint>

// Nhận vào mảng 4 phần tử (mỗi phần tử 32-bit) và trả về con trỏ của mảng đó
uint32_t* mixColumns(uint32_t state[4]);
uint32_t* invMixColumns(uint32_t state[4]);

#endif
