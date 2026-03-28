#include <iostream>
#include <array>
#include <cstring>
#include "shift_Rows.h"

using namespace std;

// Test case 1: Kết quả đã biết
void case1_known_answer() {
    array<uint32_t, 4> state    = {0xD42711AE, 0xE0BF98F1, 0xB8B45DE5, 0x1E415230};
    array<uint32_t, 4> expected = {0xD4BF5D30, 0xE0B452AE, 0xB84111F1, 0x1E2798E5};
    state = shiftRows(state);
    if (state == expected)
        cout << "[Test case 1 ] Known answer ............. PASS\n";
    else
        cout << "[Test case 1 ] Known answer ............. FAIL\n";
}

// Test case 2: Đầu vào đều là 0
void case2_all_zero() {
    array<uint32_t, 4> state    = {0, 0, 0, 0};
    array<uint32_t, 4> expected = {0, 0, 0, 0};
    state = shiftRows(state);
    if (state == expected)
        cout << "[Test case 2 ] All-zero input ........... PASS\n";
    else
        cout << "[Test case 2 ] All-zero input ........... FAIL\n";
}

// Test case 3: Đầu vào đều là cùng một giá trị
void case3_all_same() {
    array<uint32_t, 4> state    = {0xABABABAB, 0xABABABAB, 0xABABABAB, 0xABABABAB};
    array<uint32_t, 4> expected = {0xABABABAB, 0xABABABAB, 0xABABABAB, 0xABABABAB};
    state = shiftRows(state);
    if (state == expected)
        cout << "[Test case 3 ] All-same-byte ............ PASS\n";
    else
        cout << "[Test case 3 ] All-same-byte ............ FAIL\n";
}

// Test case 4: Hàng 0 không thay đổi
void case4_row0_unchanged() {
    // row0: 01 02 03 04, các hàng còn lại = 0
    array<uint32_t, 4> state    = {0x01000000, 0x02000000, 0x03000000, 0x04000000};
    array<uint32_t, 4> expected = {0x01000000, 0x02000000, 0x03000000, 0x04000000};
    state = shiftRows(state);
    if (state == expected)
        cout << "[Test case 4 ] Row 0 unchanged .......... PASS\n";
    else
        cout << "[Test case 4 ] Row 0 unchanged .......... FAIL\n";
}

// Test case 5: Hàng 1 dịch trái 1 byte
void case5_row1_shift1() {
    // row1: 0A 0B 0C 0D → sau shift: 0B 0C 0D 0A
    array<uint32_t, 4> state    = {0x000A0000, 0x000B0000, 0x000C0000, 0x000D0000};
    array<uint32_t, 4> expected = {0x000B0000, 0x000C0000, 0x000D0000, 0x000A0000};
    state = shiftRows(state);
    if (state == expected)
        cout << "[Test case 5 ] Row 1 shift left 1 ....... PASS\n";
    else
        cout << "[Test case 5 ] Row 1 shift left 1 ....... FAIL\n";
}

// Test case 6: Hàng 2 dịch trái 2 byte
void case6_row2_shift2() {
    // row2: 0A 0B 0C 0D → sau shift: 0C 0D 0A 0B
    array<uint32_t, 4> state    = {0x00000A00, 0x00000B00, 0x00000C00, 0x00000D00};
    array<uint32_t, 4> expected = {0x00000C00, 0x00000D00, 0x00000A00, 0x00000B00};
    state = shiftRows(state);
    if (state == expected)
        cout << "[Test case 6 ] Row 2 shift left 2 ....... PASS\n";
    else
        cout << "[Test case 6 ] Row 2 shift left 2 ....... FAIL\n";
}

// Test case 7: Hàng 3 dịch trái 3 byte
void case7_row3_shift3() {
    // row3: 0A 0B 0C 0D → sau shift: 0D 0A 0B 0C
    array<uint32_t, 4> state    = {0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D};
    array<uint32_t, 4> expected = {0x0000000D, 0x0000000A, 0x0000000B, 0x0000000C};
    state = shiftRows(state);
    if (state == expected)
        cout << "[Test case 7 ] Row 3 shift left 3 ....... PASS\n";
    else
        cout << "[Test case 7 ] Row 3 shift left 3 .......= FAIL\n";
}

// Test case 8: shift rồi inv shift = không đổi
void case8_inv_after_fwd() {
    array<uint32_t, 4> original = {0x3243F6A8, 0x885A308D, 0x313198A2, 0xE0370734};
    array<uint32_t, 4> state    = original;
    state = shiftRows(state);
    state = invShiftRows(state);
    if (state == original)
        cout << "[Test case 8 ] shift -> inv shift ....... PASS\n";
    else
        cout << "[Test case 8 ] shift -> inv shift ....... FAIL\n";
}

// Test case 9: inv shift rồi shift = không đổi
void case9_fwd_after_inv() {
    array<uint32_t, 4> original = {0x3243F6A8, 0x885A308D, 0x313198A2, 0xE0370734};
    array<uint32_t, 4> state    = original;
    state = invShiftRows(state);
    state = shiftRows(state);
    if (state == original)
        cout << "[Test case 9 ] inv shift -> shift ....... PASS\n";
    else
        cout << "[Test case 9 ] inv shift -> shift ....... FAIL\n";
}

// Test case 10: shiftRows 4 lần liên tiếp = không đổi (Tính chất tuần hoàn)
void case10_four_times_identity() {
    array<uint32_t, 4> original = {0x2B28AB09, 0x7EAEF7CF, 0x15D2154F, 0x16A6883C};
    array<uint32_t, 4> state    = original;
    state = shiftRows(state); state = shiftRows(state);
    state = shiftRows(state); state = shiftRows(state);
    if (state == original)
        cout << "[Test case 10] shiftRows x4 ............. PASS\n";
    else
        cout << "[Test case 10] shiftRows x4 ............. FAIL\n";
}

int main() {
    cout << "========================================\n";
    cout << "        ShiftRows Tests\n";
    cout << "========================================\n\n";

    case1_known_answer();
    case2_all_zero();
    case3_all_same();
    case4_row0_unchanged();
    case5_row1_shift1();
    case6_row2_shift2();
    case7_row3_shift3();
    case8_inv_after_fwd();
    case9_fwd_after_inv();
    case10_four_times_identity();

    return 0;
}