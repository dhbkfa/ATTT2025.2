#include <stdio.h>
#include <string.h>
#include "shift_Rows.h"

// Test case 1: Kết quả đã biết
void case1_known_answer() {
    uint8_t state[4][4] = {
        {0xD4, 0xE0, 0xB8, 0x1E},
        {0x27, 0xBF, 0xB4, 0x41},
        {0x11, 0x98, 0x5D, 0x52},
        {0xAE, 0xF1, 0xE5, 0x30}
    };
    uint8_t expected[4][4] = {
        {0xD4, 0xE0, 0xB8, 0x1E},
        {0xBF, 0xB4, 0x41, 0x27},
        {0x5D, 0x52, 0x11, 0x98},
        {0x30, 0xAE, 0xF1, 0xE5}
    };
    shiftRows(state);
    if (memcmp(state, expected, 16) == 0)
        printf("[Test case 1 ] Known answer ............. PASS\n");
    else
        printf("[Test case 1 ] Known answer ............. FAIL\n");
}

// Test case 2: Đầu vào đều là 0
void case2_all_zero() {
    uint8_t state[4][4]    = {0};
    uint8_t expected[4][4] = {0};
    shiftRows(state);
    if (memcmp(state, expected, 16) == 0)
        printf("[Test case 2 ] All-zero input ........... PASS\n");
    else
        printf("[Test case 2 ] All-zero input ........... FAIL\n");
}

// Test case 3: Đầu vào đều là cùng một giá trị
void case3_all_same() {
    uint8_t state[4][4], expected[4][4];
    memset(state,    0xAB, 16);
    memset(expected, 0xAB, 16);
    shiftRows(state);
    if (memcmp(state, expected, 16) == 0)
        printf("[Test case 3 ] All-same-byte ............ PASS\n");
    else
        printf("[Test case 3 ] All-same-byte ............ FAIL\n");
}

// Test case 4: Hàng 0 không thay đổi
void case4_row0_unchanged() {
    uint8_t state[4][4] = {
        {0x01, 0x02, 0x03, 0x04},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00}
    };
    uint8_t row0_before[4] = {0x01, 0x02, 0x03, 0x04};
    shiftRows(state);
    if (memcmp(state[0], row0_before, 4) == 0)
        printf("[Test case 4 ] Row 0 unchanged .......... PASS\n");
    else
        printf("[Test case 4 ] Row 0 unchanged .......... FAIL\n");
}

// Test case 5: Hàng 1 dịch trái 1 byte
void case5_row1_shift1() {
    uint8_t state[4][4] = {
        {0x00, 0x00, 0x00, 0x00},
        {0x0A, 0x0B, 0x0C, 0x0D},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00}
    };
    uint8_t expected_row1[4] = {0x0B, 0x0C, 0x0D, 0x0A};
    shiftRows(state);
    if (memcmp(state[1], expected_row1, 4) == 0)
        printf("[Test case 5 ] Row 1 shift left 1 ....... PASS\n");
    else
        printf("[Test case 5 ] Row 1 shift left 1 ....... FAIL\n");
}

// Test case 6: Hàng 2 dịch trái 2 byte
void case6_row2_shift2() {
    uint8_t state[4][4] = {
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x0A, 0x0B, 0x0C, 0x0D},
        {0x00, 0x00, 0x00, 0x00}
    };
    uint8_t expected_row2[4] = {0x0C, 0x0D, 0x0A, 0x0B};
    shiftRows(state);
    if (memcmp(state[2], expected_row2, 4) == 0)
        printf("[Test case 6 ] Row 2 shift left 2 ....... PASS\n");
    else
        printf("[Test case 6 ] Row 2 shift left 2 ....... FAIL\n");
}

// Test case 7: Hàng 3 dịch trái 3 byte
void case7_row3_shift3() {
    uint8_t state[4][4] = {
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x0A, 0x0B, 0x0C, 0x0D}
    };
    uint8_t expected_row3[4] = {0x0D, 0x0A, 0x0B, 0x0C};
    shiftRows(state);
    if (memcmp(state[3], expected_row3, 4) == 0)
        printf("[Test case 7 ] Row 3 shift left 3 ....... PASS\n");
    else
        printf("[Test case 7 ] Row 3 shift left 3 ....... FAIL\n");
}

// Test case 8: shift rồi inv shift = không đổi
void case8_inv_after_fwd() {
    uint8_t original[4][4] = {
        {0x32, 0x88, 0x31, 0xE0},
        {0x43, 0x5A, 0x31, 0x37},
        {0xF6, 0x30, 0x98, 0x07},
        {0xA8, 0x8D, 0xA2, 0x34}
    };
    uint8_t state[4][4];
    memcpy(state, original, 16);
    shiftRows(state);
    invShiftRows(state);
    if (memcmp(state, original, 16) == 0)
        printf("[Test case 8 ] shift -> inv shift ....... PASS\n");
    else
        printf("[Test case 8 ] shift -> inv shift ....... FAIL\n");
}

// Test case 9: inv shift rồi shift = không đổi
void case9_fwd_after_inv() {
    uint8_t original[4][4] = {
        {0x32, 0x88, 0x31, 0xE0},
        {0x43, 0x5A, 0x31, 0x37},
        {0xF6, 0x30, 0x98, 0x07},
        {0xA8, 0x8D, 0xA2, 0x34}
    };
    uint8_t state[4][4];
    memcpy(state, original, 16);
    invShiftRows(state);
    shiftRows(state);
    if (memcmp(state, original, 16) == 0)
        printf("[Test case 9 ] inv shift -> shift ....... PASS\n");
    else
        printf("[Test case 9 ] inv shift -> shift ....... FAIL\n");
}

// Test case 10: shiftRows 4 lần liên tiếp = không đổi
void case10_four_times_identity() {
    uint8_t original[4][4] = {
        {0x2B, 0x7E, 0x15, 0x16},
        {0x28, 0xAE, 0xD2, 0xA6},
        {0xAB, 0xF7, 0x15, 0x88},
        {0x09, 0xCF, 0x4F, 0x3C}
    };
    uint8_t state[4][4];
    memcpy(state, original, 16);
    shiftRows(state); shiftRows(state);
    shiftRows(state); shiftRows(state);
    if (memcmp(state, original, 16) == 0)
        printf("[Test case 10] shiftRows x4 ............. PASS\n");
    else
        printf("[Test case 10] shiftRows x4 ............. FAIL\n");
}

int main() {
    printf("========================================\n");
    printf("       ShiftRows Tests\n");
    printf("========================================\n\n");

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