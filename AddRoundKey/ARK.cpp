#include <iostream>
#include <iomanip>
#include <cstdint>

// 1. Hàm AddRoundKey: Thực hiện XOR từng byte của State với RoundKey
void AddRoundKey(uint8_t state[16], const uint8_t roundKey[16]) {
    for (int i = 0; i < 16; i++) {
        state[i] ^= roundKey[i]; // Phép toán XOR bitwise (^)
    }
}

// 2. Hàm hỗ trợ in mảng 16 byte ra màn hình dưới dạng Hex
void printHexArray(const uint8_t arr[16], const char* label) {
    std::cout << label << ": ";
    for (int i = 0; i < 16; i++) {
        // In định dạng Hex, luôn hiển thị 2 chữ số
        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') 
                  << static_cast<int>(arr[i]) << " ";
    }
    std::cout << std::dec << std::endl; // Trả lại định dạng thập phân
}

// 3. Hàm main để chạy thử nghiệm
int main() {
    // TEST VECTOR CHUẨN TỪ NIST (Phụ lục B - FIPS 197)
    
    // Plaintext (trạng thái đầu vào)
    uint8_t state[16] = {
        0x00, 0x11, 0x22, 0x33, 
        0x44, 0x55, 0x66, 0x77, 
        0x88, 0x99, 0xAA, 0xBB, 
        0xCC, 0xDD, 0xEE, 0xFF
    };

    // Khóa gốc (Cipher Key) - Trong Round 0, Round Key chính là Khóa gốc
    uint8_t roundKey[16] = {
        0x00, 0x01, 0x02, 0x03, 
        0x04, 0x05, 0x06, 0x07, 
        0x08, 0x09, 0x0A, 0x0B, 
        0x0C, 0x0D, 0x0E, 0x0F
    };

    std::cout << "--- TRUOC KHI AddRoundKey (Vong 0) ---\n";
    printHexArray(state, "State vao");
    printHexArray(roundKey, "Round Key");

    // Gọi hàm AddRoundKey
    AddRoundKey(state, roundKey);

    std::cout << "\n--- SAU KHI AddRoundKey ---\n";
    printHexArray(state, "State ra "); 

    /* * KẾT QUẢ KỲ VỌNG:
     * 00 10 20 30 40 50 60 70 80 90 A0 B0 C0 D0 E0 F0
     * * Giải thích: 
     * Byte 1: 0x00 ^ 0x00 = 0x00
     * Byte 2: 0x11 ^ 0x01 = 0x10
     * Byte 3: 0x22 ^ 0x02 = 0x20
     * ...
     */

    return 0;
}