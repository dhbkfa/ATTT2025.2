#include "mix_columns.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

// ==========================================
// HÀM HỖ TRỢ HIỂN THỊ VÀ KIỂM TRA
// ==========================================

void printState(const string& label, const uint32_t state[4]) {
    cout << left << setw(15) << label << " : ";
    for (int i = 0; i < 4; i++) {
        cout << "0x" << hex << uppercase << setfill('0') << setw(8) << state[i] << " ";
    }
    cout << dec << "\n"; // Reset về hệ thập phân
}

bool checkEquality(const uint32_t original[4], const uint32_t recovered[4]) {
    for (int i = 0; i < 4; i++) {
        if (original[i] != recovered[i]) return false;
    }
    return true;
}

void runTestCase(int testNumber, const string& testName, const uint32_t inputState[4]) {
    cout << "------------------------------------------------------------\n";
    cout << "[TEST CASE " << testNumber << "] " << testName << "\n";
    
    uint32_t state[4];
    memcpy(state, inputState, 16); // Copy 4 x 4 bytes
    
    printState("Original", state);
    
    // 1. Chạy MixColumns
    mixColumns(state);
    printState("After Mix", state);
    
    // 2. Chạy InvMixColumns
    invMixColumns(state);
    printState("After InvMix", state);
    
    // 3. Đánh giá kết quả
    if (checkEquality(inputState, state)) {
        cout << "=> RESULT        : \033[1;32mPASS\033[0m\n";
    } else {
        cout << "=> RESULT        : \033[1;31mFAIL\033[0m\n";
    }
}

// ==========================================
// MAIN: CHẠY 10 TEST CASES
// ==========================================

int main() {
    cout << "============================================================\n";
    cout << "      BẮT ĐẦU CHẠY KIỂM THỬ MIX COLUMNS & INV MIX COLUMNS     \n";
    cout << "============================================================\n";

    // Test Case 1: Dữ liệu test chuẩn từ FIPS 197 (AES Standard)
    uint32_t tc1[4] = {0xD4BF5D30, 0xE0B452AE, 0xB84111F1, 0x1E2798E5};
    runTestCase(1, "FIPS 197 Standard Vector", tc1);

    // Test Case 2: State toàn số 0 (Zero State)
    uint32_t tc2[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
    runTestCase(2, "All Zeros (Null State)", tc2);

    // Test Case 3: State toàn số 1 (FF)
    uint32_t tc3[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    runTestCase(3, "All Ones (Max Values)", tc3);

    // Test Case 4: Các byte tăng dần (Incremental State)
    uint32_t tc4[4] = {0x00010203, 0x04050607, 0x08090A0B, 0x0C0D0E0F};
    runTestCase(4, "Incremental Bytes", tc4);

    // Test Case 5: Mẫu bit xen kẽ (Alternating Bits 1010 và 0101)
    uint32_t tc5[4] = {0xAAAA5555, 0x5555AAAA, 0xAAAA5555, 0x5555AAAA};
    runTestCase(5, "Alternating Bits Pattern", tc5);

    // Test Case 6: Chỉ duy nhất 1 bit bật sáng (One-Hot state)
    uint32_t tc6[4] = {0x80000000, 0x00000000, 0x00000000, 0x00000000};
    runTestCase(6, "Single High Bit Set", tc6);

    // Test Case 7: Dữ liệu ngẫu nhiên 1
    uint32_t tc7[4] = {0x12345678, 0x9ABCDEF0, 0x2468ACE0, 0x13579BDF};
    runTestCase(7, "Random Data Block 1", tc7);

    // Test Case 8: Dữ liệu ngẫu nhiên 2 (Giá trị biên)
    uint32_t tc8[4] = {0x7F807F80, 0x807F807F, 0x01FE01FE, 0xFE01FE01};
    runTestCase(8, "Random Data Block 2 (Edge Values)", tc8);

    // Test Case 9: Lặp lại 1 cột giống hệt nhau
    uint32_t tc9[4] = {0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF, 0xDEADBEEF};
    runTestCase(9, "Identical Columns", tc9);

    // Test Case 10: State chứa các giá trị sinh từ hàm băm/mã hóa thực tế
    uint32_t tc10[4] = {0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A};
    runTestCase(10, "Real-world Pseudo-Hash State", tc10);

    cout << "------------------------------------------------------------\n";
    cout << "HOÀN THÀNH TOÀN BỘ TEST CASES.\n";
    return 0;
}