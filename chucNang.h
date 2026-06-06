#ifndef CHUCNANG_H
#define CHUCNANG_H

#include "types.h"
#include "hashmap.h"
#include "linkedlist.h"
#include "inRaManHinh.h"

/* --- Menu --- */
void inMenu(void);
void xoaBuffer(void);

/* --- Chuc nang --- */
/* 1. In toan bo danh sach lop */
void chucNang_InToanBoLop(const Lop *headLop);

/* 2. In sinh vien theo ma lop */
void chucNang_InSVTheoLop(HashMapLop *hmLop);

/* 3. Tim sinh vien theo MSSV */
void chucNang_TimSVTheoMSSV(HashMapSV *hmSV);

/* 4. Loc sinh vien theo GPA */
void chucNang_LocSVTheoGPA(const Lop *headLop);

/* 5. Them sinh vien moi */
void chucNang_ThemSinhVien(Lop **headLop, Lop **tailLop,
                            HashMapLop *hmLop, HashMapSV *hmSV);

/* 6. Xoa sinh vien */
void chucNang_XoaSinhVien(Lop **headLop, Lop **tailLop,
                           HashMapLop *hmLop, HashMapSV *hmSV);

/* 7. Cap nhat thong tin sinh vien */
void chucNang_CapNhatSV(HashMapSV *hmSV);

/* 8. Xuat file danh sach sinh vien theo lop */
void chucNang_XuatFileSVTheoLop(HashMapLop *hmLop);

/* 9. Luu du lieu ra file */
void chucNang_LuuFile(const Lop *headLop);

#endif
