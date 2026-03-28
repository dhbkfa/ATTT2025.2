#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include "SubBytes.hpp"

using namespace std;

// So sánh 2 mảng 32-bit xem có khớp nhau 100% không
bool check_equal(const uint32_t result[4], const uint32_t expected[4]) {
    for (int i = 0; i < 4; i++) { if (result[i] != expected[i]) return false; }
    return true;
}

void print_result(const string& test_name, bool passed) {
    cout << left << setw(45) << test_name << (passed ? "[ PASS ]" : "[ FAIL ]") << "\n";
}

// Test 01: Kiểm chứng hàm mã hóa với vector chuẩn của Viện NIST (FIPS-197)
void test01_fips_forward() {
    uint32_t state[4]    = {0x193DE3BE, 0xA0F4E22B, 0x9AC68D2A, 0xE9F84808};
    uint32_t expected[4] = {0xD42711AE, 0xE0BF98F1, 0xB8B45DE5, 0x1E415230};
    subBytes(state);
    print_result("Test 01: Ma hoa theo chuan FIPS-197", check_equal(state, expected));
}

// Test 02: Kiểm chứng hàm giải mã với vector chuẩn FIPS-197
void test02_fips_inverse() {
    uint32_t state[4]    = {0xD42711AE, 0xE0BF98F1, 0xB8B45DE5, 0x1E415230};
    uint32_t expected[4] = {0x193DE3BE, 0xA0F4E22B, 0x9AC68D2A, 0xE9F84808};
    invSubBytes(state);
    print_result("Test 02: Giai ma theo chuan FIPS-197", check_equal(state, expected));
}

// Test 03: Kiểm tra giá trị biên (Boundary Test) - Đầu vào toàn số 0
// Theo bảng S-box, 0x00 phải biến thành 0x63.
void test03_all_zeros() {
    uint32_t state[4]    = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
    uint32_t expected[4] = {0x63636363, 0x63636363, 0x63636363, 0x63636363}; // Sbox(00) = 63
    subBytes(state);
    print_result("Test 03: Dau vao toan 0 (0x00 -> 0x63)", check_equal(state, expected));
}

// Test 04: Kiểm tra giá trị biên (Boundary Test) - Đầu vào là mức cao nhất (0xFF)
// Theo bảng S-box, 0xFF phải biến thành 0x16.
void test04_all_ones() {
    uint32_t state[4]    = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    uint32_t expected[4] = {0x16161616, 0x16161616, 0x16161616, 0x16161616}; // Sbox(FF) = 16
    subBytes(state);
    print_result("Test 04: Dau vao toan FF (0xFF -> 0x16)", check_equal(state, expected));
}

// Test 05: Tính thuận nghịch (Reversibility) - Mã hóa xong giải mã phải ra dữ liệu gốc
// Bài test này áp dụng luôn cú pháp lồng hàm (Chaining): invSubBytes(subBytes(state))
void test05_forward_then_inverse() {
    uint32_t original[4] = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00};
    uint32_t state[4]; memcpy(state, original, 16);
    invSubBytes(subBytes(state)); 
    print_result("Test 05: Ma hoa -> Giai ma (Thuan nghich)", check_equal(state, original));
}

// Test 06: Tính thuận nghịch ngược - Giải mã trước rồi mã hóa vẫn phải ra dữ liệu gốc
void test06_inverse_then_forward() {
    uint32_t original[4] = {0xDEADBEEF, 0xCAFEBABE, 0x8BADF00D, 0x0DEFACED};
    uint32_t state[4]; memcpy(state, original, 16);
    subBytes(invSubBytes(state)); 
    print_result("Test 06: Giai ma -> Ma hoa (Thuan nghich)", check_equal(state, original));
}

// Test 07: Kiểm tra xem hàm có thực sự làm biến đổi dữ liệu hay không 
void test07_idempotence_check() {
    uint32_t original[4] = {0x12345678, 0x9ABCDEF0, 0x13579BDF, 0x2468ACE0};
    uint32_t state[4]; memcpy(state, original, 16);
    subBytes(state);
    print_result("Test 07: Kiem tra du lieu co bien doi", !check_equal(state, original));
}

// Test 08: Kiểm tra ánh xạ ngược chuẩn của S-box (0x63 giải mã phải về 0x00)
void test08_inv_zero_mapping() {
    uint32_t state[4]    = {0x63636363, 0x63636363, 0x63636363, 0x63636363};
    uint32_t expected[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
    invSubBytes(state);
    print_result("Test 08: Anh xa nguoc S-box (63 -> 00)", check_equal(state, expected));
}

// Test 09: Kiểm tra xem hàm có trả về đúng con trỏ của mảng state không 
void test09_pointer_return_check() {
    uint32_t state[4] = {0};
    uint32_t* ptr = subBytes(state);
    print_result("Test 09: Kiem tra con tro tra ve", (ptr == state));
}

// Test 10: Xử lý khối lượng lớn - Mã hóa lồng 3 lần, giải mã lồng 3 lần
void test10_multiple_iterations() {
    uint32_t original[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444444};
    uint32_t state[4]; memcpy(state, original, 16);
    subBytes(subBytes(subBytes(state)));
    invSubBytes(invSubBytes(invSubBytes(state)));
    print_result("Test 10: Kiem tra chuoi ham lap lai (x3)", check_equal(state, original));
}

int main() {
    cout << "=========================================================\n";
    cout << "        AES-128 SUB_BYTES (32-BIT ARRAY) TESTS           \n";
    cout << "=========================================================\n\n";
    test01_fips_forward(); test02_fips_inverse(); test03_all_zeros();
    test04_all_ones(); test05_forward_then_inverse(); test06_inverse_then_forward();
    test07_idempotence_check(); test08_inv_zero_mapping(); test09_pointer_return_check();
    test10_multiple_iterations();
    cout << "\n=========================================================\n";
    return 0;
}