# ShiftRows - AES-128

Phần cài đặt bước ShiftRows trong thuật toán mã hóa AES-128.

## Mô tả

ShiftRows là một trong bốn bước biến đổi chính của AES. Bước này thực hiện dịch vòng trái các hàng trong state matrix 4x4:

- Hàng 0: giữ nguyên
- Hàng 1: dịch trái 1 byte
- Hàng 2: dịch trái 2 byte
- Hàng 3: dịch trái 3 byte

State matrix được biểu diễn dưới dạng mảng 4 phần tử `uint32_t`, mỗi phần tử là 1 cột 32-bit.

## Cấu trúc thư mục
```
Project_ATTT_AES/
├── Shift_Rows_Code/
│   ├── shift_Rows.h
│   └── shift_Rows.cpp
├── Test_Code/
│   └── test_shift_Rows.cpp
└── README.md
```

## Cách chạy

Mở terminal tại thư mục gốc `Project_ATTT_AES` và chạy:
```bash
g++ Shift_Rows_Code/shift_Rows.cpp Test_Code/test_shift_Rows.cpp -I Shift_Rows_Code -o test_runner
./test_runner
```

## Kết quả kỳ vọng
```
========================================
        ShiftRows Tests
========================================

[Test case 1 ] Known answer ............. PASS
[Test case 2 ] All-zero input ........... PASS
[Test case 3 ] All-same-byte ............ PASS
[Test case 4 ] Row 0 unchanged .......... PASS
[Test case 5 ] Row 1 shift left 1 ...... PASS
[Test case 6 ] Row 2 shift left 2 ...... PASS
[Test case 7 ] Row 3 shift left 3 ...... PASS
[Test case 8 ] shift -> inv shift ....... PASS
[Test case 9 ] inv shift -> shift ....... PASS
[Test case 10] shiftRows x4 ............. PASS

========================================
```