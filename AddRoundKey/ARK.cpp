#include <iostream>
#include <iomanip>
#include <cstdint>

// Hàm AddRoundKey: Thực hiện XOR từng byte của State với RoundKey
void AddRoundKey(uint8_t state[16], const uint8_t roundKey[16]) {
    for (int i = 0; i < 16; i++) {
        state[i] ^= roundKey[i]; // Phép toán XOR bitwise (^)
    }
}

// Hàm hỗ trợ in mảng 16 byte ra màn hình dưới dạng Hex
void printHexArray(const uint8_t arr[16], const char* label) {
    std::cout << label << ": ";
    for (int i = 0; i < 16; i++) {
        // In định dạng Hex, luôn hiển thị 2 chữ số (VD: 0A thay vì A)
        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') 
                  << static_cast<int>(arr[i]) << " ";
    }
    std::cout << std::dec << std::endl; // Trả lại định dạng thập phân
}

int main() {
    // Giả sử đây là khối dữ liệu 16 byte (State) đang được mã hóa
    uint8_t state[16] = {
        0xA5, 0x01, 0x23, 0x45, 
        0x67, 0x89, 0xAB, 0xCD, 
        0xEF, 0xFE, 0xDC, 0xBA, 
        0x98, 0x76, 0x54, 0x32
    };

    // Khóa phụ của vòng hiện tại (Round Key) - 16 byte
    uint8_t roundKey[16] = {
        0x3C, 0xFF, 0x00, 0x11, 
        0x22, 0x33, 0x44, 0x55, 
        0x66, 0x77, 0x88, 0x99, 
        0xAA, 0xBB, 0xCC, 0xDD
    };

    std::cout << "--- TRUOC KHI AddRoundKey ---\n";
    printHexArray(state, "State ban dau");
    printHexArray(roundKey, "Round Key  ");

    // Thực hiện AddRoundKey
    AddRoundKey(state, roundKey);

    std::cout << "\n--- SAU KHI AddRoundKey ---\n";
    printHexArray(state, "State moi  "); 
    // Chú ý byte đầu tiên: 0xA5 ^ 0x3C = 0x99 (đúng như ví dụ trước đó)

    return 0;
}