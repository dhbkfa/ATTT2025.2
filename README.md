# AES MixColumns Implementation (C++)

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
- Tính tuyến tính (Linearity).