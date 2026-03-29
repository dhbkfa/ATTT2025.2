#include "../main.h"
// #include <iostream>
// #include <iomanip>
// using namespace std;
constexpr uint8_t gm2(uint8_t x) { return (x << 1) ^ ((x & 0x80) ? 0x1b : 0x00); }
constexpr uint8_t gm3(uint8_t x) { return gm2(x) ^ x; }
constexpr uint8_t gm4(uint8_t x) { return gm2(gm2(x)); }
constexpr uint8_t gm8(uint8_t x) { return gm2(gm4(x)); }
constexpr uint8_t gm09(uint8_t x) { return gm8(x) ^ x; }
constexpr uint8_t gm0b(uint8_t x) { return gm8(x) ^ gm2(x) ^ x; }
constexpr uint8_t gm0d(uint8_t x) { return gm8(x) ^ gm4(x) ^ x; }
constexpr uint8_t gm0e(uint8_t x) { return gm8(x) ^ gm4(x) ^ gm2(x); }

// Hàm MixColumns (Mã hóa toàn bộ State 4x32-bit)
void mixColumns(uint32_t state[4]) {
    for (int i = 0; i < 4; i++) {
        // 1. Lấy ra 1 cột 32-bit và tách thành 4 byte
        uint32_t col = state[i];
        uint8_t a0 = (col >> 24) & 0xFF;
        uint8_t a1 = (col >> 16) & 0xFF;
        uint8_t a2 = (col >> 8) & 0xFF;
        uint8_t a3 = col & 0xFF;

        // 2. Thực hiện phép nhân MixColumns
        uint8_t r0 = gm2(a0) ^ gm3(a1) ^ a2      ^ a3;
        uint8_t r1 = a0      ^ gm2(a1) ^ gm3(a2) ^ a3;
        uint8_t r2 = a0      ^ a1      ^ gm2(a2) ^ gm3(a3);
        uint8_t r3 = gm3(a0) ^ a1      ^ a2      ^ gm2(a3);

        // 3. Ghép lại thành 32-bit và ghi đè vào mảng
        state[i] = (static_cast<uint32_t>(r0) << 24) |
                   (static_cast<uint32_t>(r1) << 16) |
                   (static_cast<uint32_t>(r2) << 8)  |
                   (static_cast<uint32_t>(r3));
    }
 
}

// Hàm InvMixColumns (Giải mã toàn bộ State 4x32-bit)
void invMixColumns(uint32_t state[4]) {
    for (int i = 0; i < 4; i++) {
        uint32_t col = state[i];
        uint8_t a0 = (col >> 24) & 0xFF;
        uint8_t a1 = (col >> 16) & 0xFF;
        uint8_t a2 = (col >> 8) & 0xFF;
        uint8_t a3 = col & 0xFF;

        uint8_t r0 = gm0e(a0) ^ gm0b(a1) ^ gm0d(a2) ^ gm09(a3);
        uint8_t r1 = gm09(a0) ^ gm0e(a1) ^ gm0b(a2) ^ gm0d(a3);
        uint8_t r2 = gm0d(a0) ^ gm09(a1) ^ gm0e(a2) ^ gm0b(a3);
        uint8_t r3 = gm0b(a0) ^ gm0d(a1) ^ gm09(a2) ^ gm0e(a3);

        state[i] = (static_cast<uint32_t>(r0) << 24) |
                   (static_cast<uint32_t>(r1) << 16) |
                   (static_cast<uint32_t>(r2) << 8)  |
                   (static_cast<uint32_t>(r3));
    }
}
// void in_ketqua(uint32_t x[4],const string& text)
// {
//     cout << text << "\n";
//     for (int i = 0; i < 4; i++)
//     {
//         cout << "0x" << hex << uppercase << setfill('0') << setw(8)<< x[i];
//         cout << "\n";
//     }
    
// }
// int main()
// {
//     uint32_t w[4] = {0xD4BF5D30,0xE0B452AE,0xB84111F1,0x1E2798E5};
//     in_ketqua(w,"mix :");
// }