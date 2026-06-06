#ifndef HASHMAP_H
#define HASHMAP_H

#include "types.h"

//HASH MAP LOP

void hmLopKhoiTao(HashMapLop *hm);


//Them lop vao bang bam (chua kiem tra trung key)
void hmLopThem(HashMapLop *hm, Lop *lop);


/* Tim lop theo maLop, tra ve NULL neu khong co */
Lop *hmLopTimKiem(HashMapLop *hm, const char *maLop);

/* Xoa entry khoi bang bam (khong free node Lop, chi xoa entry) */
void hmLopXoa(HashMapLop *hm, const char *maLop);

/* Giai phong toan bo bang bam lop (khong free cac Lop node) */
void hmLopHuy(HashMapLop *hm);

//HASH MAP SINH VIEN

void hmSVKhoiTao(HashMapSV *hm);
void hmSVThem(HashMapSV *hm, SinhVien *sv);
SinhVien *hmSVTimKiem(HashMapSV *hm, const char *mssv);
void hmSVXoa(HashMapSV *hm, const char *mssv);
void hmSVHuy(HashMapSV *hm);

#endif
