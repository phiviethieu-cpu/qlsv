#ifndef TYPES_H
#define TYPES_H

#define HASH_SIZE 10007  /* kich thuoc bang bam (so nguyen to giup phan bo deu) */

typedef struct SinhVien {
    char mssv[8];
    char hoVaTen[100];
    char ngaySinh[11];   /* DD/MM/YYYY */
    char email[100];
    char sdt[15];
    char maLop[5];
    float gpa;
    struct SinhVien *next;
    struct SinhVien *prev;
} SinhVien;

typedef struct Lop {
    char maLop[5];
    char tenLop[100];
    char chuNhiemLop[100];
    int soLuongSinhVien;
    SinhVien *danhSachSV;   /* linked list sinh vien cua lop */
    SinhVien *tailSV;       /* them: giu duoi de them */
    struct Lop *next;
    struct Lop *prev;
} Lop;

/*Moi o trong bang bam la 1 linked list cac Entry (xu ly xung dot bang phuong phap chaining) */

/* Entry cua bang bam lop */
typedef struct EntryLop {
    char key[5];            /* maLop */
    Lop *lop;
    struct EntryLop *next;
} EntryLop;

/* Entry cua bang bam sinh vien */
typedef struct EntrySV {
    char key[8];            /* mssv */
    SinhVien *sv;
    struct EntrySV *next;
} EntrySV;

/* Bang bam lop */
typedef struct {
    EntryLop *buckets[HASH_SIZE];
} HashMapLop;

/* Bang bam sinh vien */
typedef struct {
    EntrySV *buckets[HASH_SIZE];
} HashMapSV;

#endif
