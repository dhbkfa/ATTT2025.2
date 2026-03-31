#include <iostream>
#include <iomanip>
#include <cstdint>
#include "mix_Columns.hpp"

// Hàm hỗ trợ kiểm tra mảng 32-bit có khớp nhau không
bool check_equal(const uint32_t result[4], const uint32_t expected[4]) {
    for (int i = 0; i < 4; i++) {
        if (result[i] != expected[i]) return false;
    }
    return true;
}

// Hàm hỗ trợ in kết quả pass/fail
void print_result(const std::string& test_name, bool passed) {
    std::cout << std::left << std::setw(45) << test_name
              << (passed ? "[ PASS ]" : "[ FAIL ]") << "\n";
}


// Test 1: Kiểm tra hàm mã hóa MixColumns với dữ liệu chuẩn FIPS-197
void test01_fips_forward() {
    uint32_t state[4]    = {0xD42711AE, 0xE0BF98F1, 0xB8B45DE5, 0x1E415230};
    uint32_t expected[4] = {0x046681E5, 0xE0CB199A, 0x48F8D37A, 0x2806264C};

    mixColumns(state);
    print_result("Test 01: FIPS 197 Known Answer (Forward)", check_equal(state, expected));
}

// Test 2: Kiểm tra hàm giải mã InvMixColumns với dữ liệu chuẩn FIPS-197
void test02_fips_inverse() {
    uint32_t state[4]    = {0x046681E5, 0xE0CB199A, 0x48F8D37A, 0x2806264C};
    uint32_t expected[4] = {0xD42711AE, 0xE0BF98F1, 0xB8B45DE5, 0x1E415230};

    invMixColumns(state);
    print_result("Test 02: FIPS 197 Known Answer (Inverse)", check_equal(state, expected));
}

// Test 3: Đầu vào toàn số 0. Mix hay InvMix thì vẫn phải ra 0.
void test03_all_zeros() {
    uint32_t state[4]    = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
    uint32_t expected[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

    mixColumns(state);
    bool pass_mix = check_equal(state, expected);

    invMixColumns(state);
    bool pass_inv = check_equal(state, expected);

    print_result("Test 03: All-Zero Input", pass_mix && pass_inv);
}

// Test 4: Đầu vào toàn FF (255). Kiểm tra xem có bị tràn bit không.
void test04_all_ones() {
    uint32_t state[4]    = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    // Output kỳ vọng khi mix toàn FF
    uint32_t expected[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000}; // Cột [FF,FF,FF,FF] mix sẽ ra 0

    mixColumns(state);
    print_result("Test 04: All-FF Input (Zeroing effect)", check_equal(state, expected));
}

// Test 5: Tính chất thuận nghịch - Mã hóa xong Giải mã sẽ về lại y như cũ
void test05_forward_then_inverse() {
    uint32_t original[4] = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00};
    uint32_t state[4];
    for(int i=0; i<4; i++) state[i] = original[i];

    invMixColumns(mixColumns(state)); // Test luôn khả năng lồng hàm (Chaining)

    print_result("Test 05: Mix -> InvMix (Reversibility)", check_equal(state, original));
}

// Test 6: Tính chất thuận nghịch - Giải mã xong Mã hóa sẽ về lại y như cũ
void test06_inverse_then_forward() {
    uint32_t original[4] = {0xDEADBEEF, 0xCAFEBABE, 0x8BADF00D, 0x0DEFACED};
    uint32_t state[4];
    for(int i=0; i<4; i++) state[i] = original[i];

    mixColumns(invMixColumns(state)); // Lồng hàm ngược lại

    print_result("Test 06: InvMix -> Mix (Reversibility)", check_equal(state, original));
}

// Test 7: Hiệu ứng khuếch tán (Diffusion) - Đổi 1 byte sẽ đổi cả cột
void test07_diffusion_property() {
    uint32_t state[4]    = {0x01000000, 0x00000000, 0x00000000, 0x00000000};
    // Nếu chỉ có 1 byte = 0x01 ở đầu, kết quả phải ra đúng ma trận nhân [02, 01, 01, 03]
    uint32_t expected[4] = {0x02010103, 0x00000000, 0x00000000, 0x00000000};

    mixColumns(state);
    print_result("Test 07: Single Byte Diffusion", check_equal(state, expected));
}

// Test 8: Các cột độc lập với nhau (Column Independence)
void test08_column_independence() {
    uint32_t state1[4] = {0xAABBCCDD, 0x00000000, 0x00000000, 0x00000000};
    uint32_t state2[4] = {0xAABBCCDD, 0xFFFFFFFF, 0x12345678, 0x9ABCDEF0};

    mixColumns(state1);
    mixColumns(state2);

    // Cột 0 của cả 2 state phải giống hệt nhau dù các cột khác khác nhau
    bool passed = (state1[0] == state2[0]);
    print_result("Test 08: Column Independence", passed);
}

// Test 9: Tính chất tuyến tính: Mix(A) ^ Mix(B) == Mix(A ^ B)
void test09_linearity() {
    uint32_t state_A[4]   = {0x12345678, 0x9ABCDEF0, 0x11111111, 0x22222222};
    uint32_t state_B[4]   = {0xFEDCBA98, 0x76543210, 0xEEEEEEEE, 0xDDDDDDDD};
    uint32_t state_XOR[4];

    for(int i=0; i<4; i++) state_XOR[i] = state_A[i] ^ state_B[i];

    mixColumns(state_A);
    mixColumns(state_B);
    mixColumns(state_XOR);

    bool passed = true;
    for(int i=0; i<4; i++) {
        if (state_XOR[i] != (state_A[i] ^ state_B[i])) passed = false;
    }

    print_result("Test 09: Linearity ( Mix(A^B) == Mix(A)^Mix(B) )", passed);
}

// Test 10: Xử lý lặp MixColumns 4 lần liên tiếp không làm hỏng dữ liệu
void test10_multiple_iterations() {
    uint32_t original[4] = {0x13579BDF, 0x2468ACE0, 0xF0F0F0F0, 0x0F0F0F0F};
    uint32_t state[4];
    for(int i=0; i<4; i++) state[i] = original[i];

    // Mix 4 lần
    mixColumns(state); mixColumns(state);
    mixColumns(state); mixColumns(state);

    // Giải mã 4 lần
    invMixColumns(state); invMixColumns(state);
    invMixColumns(state); invMixColumns(state);

    print_result("Test 10: Multiple Iterations (x4)", check_equal(state, original));
}

// ---------------------------------------------------------
// MAIN FUNCTION
// ---------------------------------------------------------
int main() {
    std::cout << "=========================================================\n";
    std::cout << "          AES-128 MIX_COLUMNS (32-BIT ARRAY) TESTS       \n";
    std::cout << "=========================================================\n\n";

    test01_fips_forward();
    test02_fips_inverse();
    test03_all_zeros();
    test04_all_ones();
    test05_forward_then_inverse();
    test06_inverse_then_forward();
    test07_diffusion_property();
    test08_column_independence();
    test09_linearity();
    test10_multiple_iterations();

    std::cout << "\n=========================================================\n";
    std::cout << " All tests completed.\n";
    std::cout << "=========================================================\n";
    std::system("pause");
    return 0;
}
