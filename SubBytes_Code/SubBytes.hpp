#ifndef SUBBYTES_HPP
#define SUBBYTES_HPP

#include <cstdint>

/**
 * SubBytes.hpp
 * Khai báo các hàm mã hóa và giải mã SubBytes cho thuật toán AES-128.
 * Đối tượng xử lý là mảng 4 phần tử 32-bit (State).
 */

// Hàm thực hiện bước SubBytes (Mã hóa)
uint32_t* subBytes(uint32_t state[4]);

// Hàm thực hiện bước Inverse SubBytes (Giải mã)
uint32_t* invSubBytes(uint32_t state[4]);

#endif // SUBBYTES_HPP