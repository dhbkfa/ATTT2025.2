
#Du an cua nhom 4


#Module 1: Substitute Bytes (SubBytes): Thay thế Byte
1. Tổng quan thuật toán

SubBytes (Thay thế Byte) là quá trình biến đổi phi tuyến tính (non-linear) duy nhất trong AES. Hàm này thực hiện việc ánh xạ độc lập từng byte của ma trận trạng thái (State) thành một byte mới dựa trên bảng tra cứu S-Box (Substitution Box). Quá trình này giúp tạo ra tính "hỗn loạn" (Confusion), làm ẩn đi mối liên hệ giữa khóa bí mật và bản mã, chống lại các cuộc tấn công phân tích mật mã.
2. Cấu trúc Module

Module này bao gồm các file sau:

    SubBytes.hpp: Chứa khai báo hàm và định nghĩa bảng sbox, rsbox (Inverse S-Box).
    SubBytes.cpp: Chứa logic thực thi của quá trình bóc tách bit và tra bảng.
    SubBytes_test.cpp: Chứa 10 kịch bản kiểm thử (testcases) toàn diện để xác thực độ chính xác của hàm.
    README.md: Tài liệu mô tả module.

3. Phân tích Input và Output

Thay vì dùng ma trận uint8_t[4][4], module này được tối ưu hóa để chạy trên mảng 4 phần tử 32-bit (đại diện cho 4 cột của ma trận State).

    Input: Mảng uint32_t state[4]. Kích thước tổng cộng là 4 x 32 bit = 128 bit (16 byte). Mỗi phần tử state[i] chứa 4 byte của 1 cột.
    Output: Trả về con trỏ uint32_t* trỏ đến chính mảng state ban đầu nhưng dữ liệu bên trong đã được thay thế để tiết kiệm bộ nhớ.

4. Giải thích Hàm & Quá trình thực thi (Process)
Hàm subBytes(uint32_t state[4])

Ánh xạ đến: Quá trình mã hóa (Encryption) - Hàm SubBytes.

Quá trình xử lý (Process) và Định nghĩa biến:

    Duyệt qua 4 cột: Dùng vòng lặp for (int i = 0; i < 4; i++) để xử lý từng cột word (32-bit).
    Bóc tách Byte (Extraction): Dùng phép dịch bit (>>) và mặt nạ (& 0xFF) để cắt 32-bit thành 4 biến 8-bit riêng biệt:
        b0: Lấy 8 bit cao nhất (dịch phải 24 bit). Tra vào sbox.
        b1: Lấy 8 bit tiếp theo (dịch phải 16 bit). Tra vào sbox.
        b2: Lấy 8 bit tiếp theo (dịch phải 8 bit). Tra vào sbox.
        b3: Lấy 8 bit thấp nhất (không dịch). Tra vào sbox.
    Đóng gói lại (Repacking): Dùng phép dịch trái (<<) và toán tử HOẶC (|) để ghép 4 byte b0, b1, b2, b3 (sau khi tra bảng) ngược lại thành khối 32-bit và ghi đè vào state[i].

Hàm invSubBytes(uint32_t state[4])

Ánh xạ đến: Quá trình giải mã (Decryption) - Hàm InvSubBytes.

    Thuật toán tương tự như subBytes, nhưng biến số đầu vào sẽ được đem tra cứu tại bảng rsbox (Inverse S-Box) để khôi phục lại giá trị dữ liệu ban đầu.

5. Kịch bản Kiểm thử (Testcases)

Để đảm bảo hàm chạy đúng 100%, file test cung cấp 10 testcases, bao phủ các trường hợp:

    Test 01 & 02 (FIPS-197 Standard): Đối chiếu input/output với vector chuẩn của viện NIST.
    Test 03 & 04 (Boundary): Kiểm tra các giá trị biên toàn 0x00 và toàn 0xFF.
    Test 05 & 06 (Reversibility): Đảm bảo mã hóa xong giải mã (và ngược lại) trả về đúng dữ liệu gốc.
    Test 07 (Idempotence): Xác nhận hàm thực sự làm thay đổi dữ liệu (không trả về chuỗi cũ).
    Test 08: Kiểm tra ánh xạ ngược chuẩn của RS-Box (0x63 khôi phục về 0x00).
    Test 09: Kiểm tra tính toàn vẹn của con trỏ mảng trả về.
    Test 10 (Stress Test): Mã hóa và giải mã lồng nhau 3 lần liên tục.

6. Hướng dẫn Biên dịch và Chạy Test

Yêu cầu hệ thống cài đặt trình biên dịch C++ (G++ hoặc Clang). Mở terminal tại thư mục chứa code và chạy lệnh sau:

# 1. Biên dịch file test
g++ SubBytes_TestCode/SubBytes_test.cpp SubBytes_Code/SubBytes.cpp -o test_runner
# 2. Chạy file thực thi
./test_runner

# 3. Kết quả test
=========================================================
        AES-128 SUB_BYTES (32-BIT ARRAY) TESTS           
=========================================================

Test 01: Ma hoa theo chuan FIPS-197           [ PASS ]
Test 02: Giai ma theo chuan FIPS-197          [ PASS ]
Test 03: Dau vao toan 0 (0x00 -> 0x63)        [ PASS ]
Test 04: Dau vao toan FF (0xFF -> 0x16)       [ PASS ]
Test 05: Ma hoa -> Giai ma (Thuan nghich)     [ PASS ]
Test 06: Giai ma -> Ma hoa (Thuan nghich)     [ PASS ]
Test 07: Kiem tra du lieu co bien doi         [ PASS ]
Test 08: Anh xa nguoc S-box (63 -> 00)        [ PASS ]
Test 09: Kiem tra con tro tra ve (Chaining)   [ PASS ]
Test 10: Kiem tra chuoi ham lap lai (x3)      [ PASS ]

=========================================================












# Module 2 : ShiftRows - AES-128

## Mô tả

ShiftRows là một trong bốn bước biến đổi chính của AES. Bước này thực hiện dịch vòng trái các hàng trong state matrix 4x4:

- Hàng 0: giữ nguyên
- Hàng 1: dịch trái 1 byte
- Hàng 2: dịch trái 2 byte
- Hàng 3: dịch trái 3 byte

State matrix được biểu diễn dưới dạng mảng 4 phần tử `uint32_t`, mỗi phần tử là 1 cột 32-bit.



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




#Module 3:AES MixColumns Implementation (C++)

Dự án này thực hiện bước **Mix Columns** và **Inverse Mix Columns** trong thuật toán mã hóa khối AES (Advanced Encryption Standard). Code được tối ưu hóa để xử lý mảng 32-bit (State 4x32-bit).

## Tính năng
- **Input/Output**: Xử lý trực tiếp trên cột 32-bit (uint32_t).
- **Chaining support**: Hàm trả về con trỏ mảng, cho phép lồng các hàm mã hóa.

## Cấu trúc thư mục
* **mix_columns_code/**: Chứa mã nguồn thực hiện thuật toán.
  * `mix_columns.cpp`: Logic xử lý nhân ma trận trong trường hữu hạn $GF(2^8)$.
  * `mix_Columns.hpp`: Khai báo hàm và các hàm nhân Galois (gm2, gm3...).
* **Test_Code_MC/**: Chứa mã nguồn kiểm thử.
  * `test_code.cpp`: 10 test cases bao gồm kiểm tra tính thuận nghịch, khuếch tán và dữ liệu chuẩn FIPS-197.
* **.gitignore**: Cấu hình bỏ qua các file rác khi build.

## Cách biên dịch và chạy
Biên dịch bằng dòng lệnh (Terminal/Command Prompt) bằng `g++`:

##  Kết quả kiểm thử
Dự án bao gồm 10 Test Cases bao phủ:
- Dữ liệu chuẩn FIPS-197.
- Tính thuận nghịch (Mix -> InvMix).
- Hiệu ứng khuếch tán (Diffusion).
- Tính tuyến tính (Linearity)

