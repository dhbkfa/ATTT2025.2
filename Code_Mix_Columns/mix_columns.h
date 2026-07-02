/**
 * @file mix_columns.h
 * @brief Định nghĩa và tối ưu hóa các hàm MixColumns và InvMixColumns cho AES.
 * @version 2.0 (Production Grade)
 */

#ifndef AES_MIX_COLUMNS_H
#define AES_MIX_COLUMNS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Thực hiện phép biến đổi MixColumns trên State matrix.
 * Phép toán được thực hiện trên trường Galois GF(2^8).
 * * @param state Mảng 4 phần tử 32-bit (đại diện cho 16 byte của AES State).
 */
void mixColumns(uint32_t state[4]);

/**
 * @brief Thực hiện phép biến đổi Inverse MixColumns (giải mã).
 * Khôi phục lại State matrix trước khi qua MixColumns.
 * * @param state Mảng 4 phần tử 32-bit (đại diện cho 16 byte của AES State).
 */
void invMixColumns(uint32_t state[4]);

#ifdef __cplusplus
}
#endif

#endif // AES_MIX_COLUMNS_H