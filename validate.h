#ifndef VALIDATE_H
#define VALIDATE_H

/* ================================================================
   KIEM TRA RANG BUOC NHAP DU LIEU
   Moi ham tra ve 1 neu hop le, 0 neu khong hop le.
   ================================================================ */

/*
 * Kiem tra MSSV:
 *   - Khong rong
 *   - Do dai 1-7 ky tu
 *   - Chi chua chu cai (A-Z, a-z) va chu so (0-9)
 */
int isValidMSSV(const char *mssv);

/*
 * Kiem tra ho va ten:
 *   - Khong rong, khong chi la khoang trang
 *   - Do dai 2-99 ky tu
 *   - Chi chua chu cai, khoang trang, dau gach ngang
 *   (Ho tro tieng Viet qua ky tu da byte)
 */
int isValidHoVaTen(const char *ten);

/*
 * Kiem tra ngay sinh dinh dang DD/MM/YYYY:
 *   - Dung dinh dang DD/MM/YYYY
 *   - Ngay: 1-31, thang: 1-12, nam: 1900-2099
 *   - Kiem tra so ngay hop le theo thang (ca nam nhuan)
 */
int isValidNgaySinh(const char *ngay);

/*
 * Kiem tra email:
 *   - Co dung mot ky tu '@'
 *   - Phan truoc '@' khong rong
 *   - Phan sau '@' co it nhat mot dau '.' va khong rong hai ben
 *   - Do dai toi da 99 ky tu
 */
int isValidEmail(const char *email);

/*
 * Kiem tra so dien thoai (dinh dang Viet Nam):
 *   - Chi chua chu so, co the bat dau bang '+'
 *   - Do dai 9-12 chu so (sau khi bo dau '+')
 *   - Neu bat dau bang '0': 10 chu so
 *   - Neu bat dau bang '+84': 11-12 ky tu tong
 */
int isValidSDT(const char *sdt);

/*
 * Kiem tra ma lop:
 *   - Khong rong
 *   - Do dai 1-4 ky tu
 *   - Chi chua chu cai va chu so
 */
int isValidMaLop(const char *maLop);

/*
 * Chuyen chuoi thanh GPA va kiem tra:
 *   - Phai la so thuc hop le (khong chua ky tu la)
 *   - Nam trong khoang [0.0, 4.0]
 *   - Luu ket qua vao con tro *out neu hop le
 */
int isValidGPA(const char *input, float *out);

/* ================================================================
   HAM TIEN ICH HO TRO VALIDATE
   ================================================================ */

/* Kiem tra nam nhuan */
int laNamNhuan(int nam);

/* Kiem tra so ngay hop le theo thang va nam */
int soNgayHopLe(int ngay, int thang, int nam);

#endif /* VALIDATE_H */
