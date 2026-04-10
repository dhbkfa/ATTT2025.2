# 🔐 Dự án Mã hóa và Giải mã thuật toán AES (C++)

> **Thực hiện bởi Nhóm 4**
>
> Dự án triển khai hệ thống mã hóa và giải mã chuẩn bảo mật **AES-128**. Mã nguồn được thiết kế dưới dạng cấu trúc hướng module linh hoạt và tối ưu hóa cấp phát bộ nhớ thấp nhất có thể bằng công nghệ chỉnh sửa trực tiếp (In-place modification) trên các khối 32-bit `uint32_t`.

---

## 🚀 Hướng dẫn Sử dụng (Quick Start)

**1. Biên dịch mã nguồn:** Mở terminal tại thư mục `ATTT2025.2` và gõ lệnh sau để hệ thống tự build:
```bash
make
```

**2. Khởi chạy chương trình:**
```bash
./main
```

**3. Làm theo hướng dẫn trên màn hình:**
- **Mã hóa (Encrypt):** Gõ `Y`, nhập Bản rõ (128-bit) và Khóa gốc (128-bit) ở định dạng HEX (Mỗi chuỗi 32 ký tự). Ví dụ: `3243F6A8885A308D313198A2E0370734`
- **Giải mã (Decrypt):** Gõ `N`, nhập Bản mã và Khóa gốc y hệt như trên.
- Hệ thống sẽ hiện cụ thể sự thay đổi của các vector 16-byte theo từng bước và trả về thông tin cuối cùng cho bạn!

---

## 📁 Kiến trúc Mã nguồn (Module Structure)

Chúng tôi đã phân chia thuật toán lõi AES làm 5 module độc lập. Mỗi module có chứa file `.h` và `.cpp` của riêng mình:

*   `main.cpp` & `Makefile`: Điều hướng thuật toán (Control Flow) và build project.
*   `Key_Expansion/`: Chịu trách nhiệm mở rộng Khóa gốc (16 byte) thành 11 Khóa vòng (Round Keys) dùng để chèn vào mỗi bước.
*   `AddRoundKey/`: Tối ưu hóa phép XOR vòng thay vì xử lý 16 byte con, code đọc và trộn 4 khối 32-bit (Word) đè trực tiếp lên ma trận trạng thái (State).
*   `SubBytes_Code/`: Bóc tách và Ánh xạ phi tuyến tính (Substitution Box). Chống lại các đoạn mã hóa phân tích tương quan tuyến tính.
*   `Shift_Rows_Code/`: Dịch vòng (Shift) thay đổi vị trí các byte trong các hàng của ma trận đồ thị.
*   `Code_Mix_Columns/`: Nhân ma trận đa thức trong trường hữu hạn Galois Field $GF(2^8)$ giúp xáo trộn cực mạnh các bit (Khuếch tán - Diffusion).

---

## 📚 Tóm tắt lý thuyết các Vòng (Rounds)

Thuật toán của dự án thực thi chuẩn **AES-128** tương ứng với **10 vòng lặp (Rounds)**. 

### Bước khởi tạo (Initial Round)
- `AddRoundKey()`

### Vòng 1 đến Vòng 9 (Main Rounds)
Mỗi vòng thực hiện tuần tự đủ 4 hàm:
1. `SubBytes()`
2. `ShiftRows()`
3. `MixColumns()`
4. `AddRoundKey()`

### Vòng 10 (Final Round)
Vòng lặp cuối cùng bỏ qua bước khuếch tán để cân bằng thuật toán giải mã:
1. `SubBytes()`
2. `ShiftRows()`
3. `AddRoundKey()`

Toàn bộ các bước này đều có phiên bản đảo ngược (Inverse) tương ứng được viết trong các file module (như `invSubBytes`, `invShiftRows`, `invMixColumns`) dành riêng cho chức năng **Giải mã (Decryption)** ở hàm `main()`.

---

## 🧪 Hệ thống Kiểm thử
Các module đều đã chạy qua các hệ thống kiểm thử độc lập với hơn 10 kịch bản mô phỏng Testcases tương đương **Vector Chuẩn FIPS-197** của Viện Tiêu chuẩn và Công nghệ Quốc gia Hoa Kỳ (NIST). 
```
