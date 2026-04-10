#include "ARK.h"
#include <cstdint>

/*
#include <iomanip>
#include <iostream>

// Hàm ghép 4 byte thành 1 word 32-bit (Đại diện cho 1 Cột trong State)
uint32_t packBytesToWord(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
  return (static_cast<uint32_t>(b0) << 24) | (static_cast<uint32_t>(b1) << 16) |
         (static_cast<uint32_t>(b2) << 8) | (static_cast<uint32_t>(b3));
}

// Hàm in mảng 4 word ra dạng ma trận Hex 16 byte để dễ đối chiếu
void printStateAsHex(const uint32_t state[4], const char *label) {
  std::cout << label << ":\n";
  for (int i = 0; i < 4; i++) {
    std::cout << "  Cot " << i << " (Word " << i << "): 0x" << std::hex
              << std::uppercase << std::setw(8) << std::setfill('0') << state[i]
              << std::endl;
  }
  std::cout << std::dec; // Trả lại định dạng thập phân
}
*/

// Hàm AddRoundKey siêu tốc: XOR 4 word 32-bit thay vì 16 byte
// Đầu vào là mảng 4 phần tử 32-bit (chính là 4 cột của ma trận State)
void AddRoundKey(uint32_t state[4], const uint32_t roundKey[4]) {
  for (int i = 0; i < 4; i++) {
    state[i] ^= roundKey[i]; // Mỗi lần XOR sẽ xử lý trọn vẹn 1 cột (4 byte) cùng lúc
  }
}

/*
int main() {
    // TEST VECTOR CHUẨN TỪ NIST (AES-128, Round 0)

    //luồng 16 byte dữ liệu thô ban đầu (Plaintext)
    uint8_t rawState[16] = {
        0x00, 0x11, 0x22, 0x33, // Cột 0
        0x44, 0x55, 0x66, 0x77, // Cột 1
        0x88, 0x99, 0xAA, 0xBB, // Cột 2
        0xCC, 0xDD, 0xEE, 0xFF  // Cột 3
    };

    uint8_t rawKey[16] = {
        0x00, 0x01, 0x02, 0x03, // Cột 0
        0x04, 0x05, 0x06, 0x07, // Cột 1
        0x08, 0x09, 0x0A, 0x0B, // Cột 2
        0x0C, 0x0D, 0x0E, 0x0F  // Cột 3
    };

    uint32_t state[4];
    uint32_t roundKey[4];

    //Gom 16 byte thành 4 cột 32-bit
    for (int i = 0; i < 4; i++) {
        // Lấy 4 byte liên tiếp ghép thành 1 word
        state[i] = packBytesToWord(rawState[i*4], rawState[i*4 + 1],
                                   rawState[i*4 + 2], rawState[i*4 + 3]);
        roundKey[i] = packBytesToWord(rawKey[i*4], rawKey[i*4 + 1],
                                      rawKey[i*4 + 2], rawKey[i*4 + 3]);
    }

    std::cout << "--- TRUOC KHI AddRoundKey ---\n";
    printStateAsHex(state, "State ban dau");
    printStateAsHex(roundKey, "Round Key");

    AddRoundKey(state, roundKey);

    std::cout << "\n--- SAU KHI AddRoundKey ---\n";
    printStateAsHex(state, "State ket qua");

    // KẾT QUẢ KỲ VỌNG (Đúng chuẩn NIST):
    // Cột 0: 0x00102030
    // Cột 1: 0x40506070
    // Cột 2: 0x8090A0B0
    // Cột 3: 0xC0D0E0F0

    return 0;
}
*/