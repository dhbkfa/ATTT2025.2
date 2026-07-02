/**
 * @file mix_columns.h
 * @brief Định nghĩa các hàm MixColumns và InvMixColumns cho thuật toán AES.
 * @version 1.0
 */

#ifndef MIX_COLUMNS_H
#define MIX_COLUMNS_H

#include <stdint.h>

/**
 * @brief Thực hiện phép biến đổi MixColumns trên State.
 * @param state Mảng 4 phần tử 32-bit đại diện cho State matrix.
 */
void mixColumns(uint32_t state[4]);

/**
 * @brief Thực hiện phép biến đổi InvMixColumns (giải mã) trên State.
 * @param state Mảng 4 phần tử 32-bit đại diện cho State matrix.
 */
void invMixColumns(uint32_t state[4]);

#endif // MIX_COLUMNS_H