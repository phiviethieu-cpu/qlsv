#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "hashmap.h"
#include "linkedlist.h"
#include "inRaManHinh.h"
#include "chucNang.h"
#include "validate.h"

/* ================================================================
   TIEN ICH
   ================================================================ */

void xoaBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inMenu(void)
{
    printf("\n");
    printf("========================================\n");
    printf("   QUAN LY SINH VIEN - NHOM 8\n");
    printf("========================================\n");
    printf("  1. In toan bo danh sach lop\n");
    printf("  2. In sinh vien theo ma lop\n");
    printf("  3. Tim sinh vien theo MSSV\n");
    printf("  4. Loc sinh vien theo GPA\n");
    printf("  5. Them sinh vien moi\n");
    printf("  6. Xoa sinh vien\n");
    printf("  7. Cap nhat thong tin sinh vien\n");
    printf("  8. Xuat file sinh vien theo lop\n");
    printf("  0. Thoat\n");
    printf("========================================\n");
    printf("Lua chon: ");
}

/* ================================================================
   1. IN TOAN BO DANH SACH LOP
   ================================================================ */

void chucNang_InToanBoLop(const Lop *headLop)
{
    if (!headLop) {
        printf("[INFO] Chua co du lieu lop nao.\n");
        return;
    }
    printf("\n=== DANH SACH TAT CA CAC LOP ===\n");
    inToanBoLop(headLop);
}

/* ================================================================
   2. IN SINH VIEN THEO MA LOP
   ================================================================ */

void chucNang_InSVTheoLop(HashMapLop *hmLop)
{
    char maLop[10];
    printf("Nhap ma lop: ");
    if (scanf("%9s", maLop) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    Lop *lop = hmLopTimKiem(hmLop, maLop);
    if (!lop) {
        printf("[LOI] Khong tim thay lop '%s'.\n", maLop);
        return;
    }
    printf("\n");
    inDanhSachLop(lop);
}

/* ================================================================
   3. TIM SINH VIEN THEO MSSV
   ================================================================ */

void chucNang_TimSVTheoMSSV(HashMapSV *hmSV)
{
    char mssv[10];
    printf("Nhap MSSV: ");
    if (scanf("%9s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    SinhVien *sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("[LOI] Khong tim thay sinh vien MSSV = '%s'.\n", mssv);
        return;
    }
    printf("\n--- Ket qua tim kiem ---\n");
    inThongTinSV(sv);
}

/* ================================================================
   4. LOC SINH VIEN THEO GPA
   ================================================================ */

void chucNang_LocSVTheoGPA(const Lop *headLop)
{
    float minGPA, maxGPA;
    char buf[20];

    printf("Nhap GPA toi thieu (0.00 - 4.00): ");
    if (scanf("%19s", buf) != 1) { xoaBuffer(); return; }
    xoaBuffer();
    if (!isValidGPA(buf, &minGPA)) return;

    printf("Nhap GPA toi da (0.00 - 4.00): ");
    if (scanf("%19s", buf) != 1) { xoaBuffer(); return; }
    xoaBuffer();
    if (!isValidGPA(buf, &maxGPA)) return;

    if (minGPA > maxGPA) {
        printf("[LOI] GPA toi thieu khong the lon hon GPA toi da.\n");
        return;
    }

    int soKetQua = 0;
    printf("\n--- Sinh vien co GPA tu %.2f den %.2f ---\n", minGPA, maxGPA);

    const Lop *lop = headLop;
    while (lop) {
        const SinhVien *sv = lop->danhSachSV;
        while (sv) {
            if (sv->gpa >= minGPA && sv->gpa <= maxGPA) {
                inThongTinSV(sv);
                printf("  ----------\n");
                soKetQua++;
            }
            sv = sv->next;
        }
        lop = lop->next;
    }

    if (soKetQua == 0)
        printf("[INFO] Khong tim thay sinh vien nao trong khoang GPA [%.2f, %.2f].\n", minGPA, maxGPA);
    else
        printf("[INFO] Tim thay %d sinh vien.\n", soKetQua);
}

/* ================================================================
   5. THEM SINH VIEN MOI  (co kiem tra rang buoc)
   ================================================================ */

void chucNang_ThemSinhVien(Lop **headLop, Lop **tailLop,
                            HashMapLop *hmLop, HashMapSV *hmSV)
{
    SinhVien sv;
    memset(&sv, 0, sizeof(sv));
    char buf[100];

    /* --- Nhap & validate MSSV --- */
    do {
        printf("Nhap MSSV (toi da 7 ky tu): ");
        if (scanf("%7s", sv.mssv) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidMSSV(sv.mssv));

    if (hmSVTimKiem(hmSV, sv.mssv)) {
        printf("[LOI] MSSV '%s' da ton tai.\n", sv.mssv);
        return;
    }

    /* --- Nhap & validate ho va ten --- */
    do {
        printf("Nhap ho va ten: ");
        if (scanf(" %99[^\n]", sv.hoVaTen) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidHoVaTen(sv.hoVaTen));

    /* --- Nhap & validate ngay sinh --- */
    do {
        printf("Nhap ngay sinh (DD/MM/YYYY): ");
        if (scanf("%10s", sv.ngaySinh) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidNgaySinh(sv.ngaySinh));

    /* --- Nhap & validate email --- */
    do {
        printf("Nhap email: ");
        if (scanf("%99s", sv.email) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidEmail(sv.email));

    /* --- Nhap & validate SDT --- */
    do {
        printf("Nhap so dien thoai: ");
        if (scanf("%14s", sv.sdt) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidSDT(sv.sdt));

    /* --- Nhap & validate ma lop --- */
    do {
        printf("Nhap ma lop: ");
        if (scanf("%4s", sv.maLop) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidMaLop(sv.maLop));

    /* Kiem tra lop co ton tai khong */
    Lop *lop = hmLopTimKiem(hmLop, sv.maLop);
    if (!lop) {
        printf("[LOI] Lop '%s' khong ton tai. Ban co muon tao lop moi? (c/k): ", sv.maLop);
        char choice;
        if (scanf(" %c", &choice) != 1) { xoaBuffer(); return; }
        xoaBuffer();

        if (choice == 'c' || choice == 'C') {
            Lop lopMoi;
            memset(&lopMoi, 0, sizeof(lopMoi));
            strncpy(lopMoi.maLop, sv.maLop, sizeof(lopMoi.maLop) - 1);

            do {
                printf("Nhap ten lop: ");
                if (scanf(" %99[^\n]", lopMoi.tenLop) != 1) { xoaBuffer(); return; }
                xoaBuffer();
            } while (!isValidHoVaTen(lopMoi.tenLop)); /* dung chung ham check chuoi hop le */

            do {
                printf("Nhap ten chu nhiem lop: ");
                if (scanf(" %99[^\n]", lopMoi.chuNhiemLop) != 1) { xoaBuffer(); return; }
                xoaBuffer();
            } while (!isValidHoVaTen(lopMoi.chuNhiemLop));

            lopMoi.soLuongSinhVien = 0;
            lopMoi.danhSachSV = NULL;
            lopMoi.tailSV = NULL;

            Lop *nodeLop = taoNodeLop(lopMoi);
            if (!nodeLop) { printf("[LOI] Khong du bo nho.\n"); return; }
            themVaoLLLop(headLop, tailLop, nodeLop);
            hmLopThem(hmLop, nodeLop);
            lop = nodeLop;
            printf("[OK] Da tao lop '%s'.\n", lop->maLop);
        } else {
            printf("[INFO] Huy them sinh vien.\n");
            return;
        }
    }

    /* --- Nhap & validate GPA --- */
    do {
        printf("Nhap GPA (0.00 - 4.00): ");
        if (scanf("%99s", buf) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidGPA(buf, &sv.gpa));

    /* --- Tao node va them vao cau truc --- */
    SinhVien *node = taoNodeSinhVien(sv);
    if (!node) { printf("[LOI] Khong du bo nho.\n"); return; }

    themVaoLLSV(&lop->danhSachSV, &lop->tailSV, node);
    lop->soLuongSinhVien++;
    hmSVThem(hmSV, node);

    printf("[OK] Da them sinh vien '%s' - %s vao lop %s.\n",
           node->mssv, node->hoVaTen, node->maLop);
}

/* ================================================================
   6. XOA SINH VIEN
   ================================================================ */

void chucNang_XoaSinhVien(Lop **headLop, Lop **tailLop,
                           HashMapLop *hmLop, HashMapSV *hmSV)
{
    (void)headLop; (void)tailLop;

    char mssv[10];
    printf("Nhap MSSV can xoa: ");
    if (scanf("%9s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    if (!isValidMSSV(mssv)) return;

    SinhVien *sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("[LOI] Khong tim thay sinh vien MSSV = '%s'.\n", mssv);
        return;
    }

    printf("\nThong tin sinh vien can xoa:\n");
    inThongTinSV(sv);
    printf("Xac nhan xoa? (c/k): ");
    char choice;
    if (scanf(" %c", &choice) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    if (choice != 'c' && choice != 'C') {
        printf("[INFO] Huy thao tac xoa.\n");
        return;
    }

    Lop *lop = hmLopTimKiem(hmLop, sv->maLop);
    if (lop) {
        xoaSinhVien(&lop->danhSachSV, &lop->tailSV, sv);
        if (lop->soLuongSinhVien > 0)
            lop->soLuongSinhVien--;
    } else {
        free(sv);
    }

    hmSVXoa(hmSV, mssv);
    printf("[OK] Da xoa sinh vien MSSV = '%s'.\n", mssv);
}

/* ================================================================
   7. CAP NHAT THONG TIN SINH VIEN  (co kiem tra rang buoc)
   ================================================================ */

void chucNang_CapNhatSV(HashMapSV *hmSV)
{
    char mssv[10];
    printf("Nhap MSSV can cap nhat: ");
    if (scanf("%9s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    SinhVien *sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("[LOI] Khong tim thay sinh vien MSSV = '%s'.\n", mssv);
        return;
    }

    printf("\nThong tin hien tai:\n");
    inThongTinSV(sv);
    printf("\n--- Cap nhat (nhan Enter de giu nguyen) ---\n");

    char buf[100];

    /* Ho va ten */
    printf("Ho va ten [%s]: ", sv->hoVaTen);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        if (isValidHoVaTen(buf))
            strncpy(sv->hoVaTen, buf, sizeof(sv->hoVaTen) - 1);
        else
            printf("  -> Giu nguyen gia tri cu.\n");
    }

    /* Ngay sinh */
    printf("Ngay sinh [%s]: ", sv->ngaySinh);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        if (isValidNgaySinh(buf))
            strncpy(sv->ngaySinh, buf, sizeof(sv->ngaySinh) - 1);
        else
            printf("  -> Giu nguyen gia tri cu.\n");
    }

    /* Email */
    printf("Email [%s]: ", sv->email);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        if (isValidEmail(buf))
            strncpy(sv->email, buf, sizeof(sv->email) - 1);
        else
            printf("  -> Giu nguyen gia tri cu.\n");
    }

    /* SDT */
    printf("SDT [%s]: ", sv->sdt);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        if (isValidSDT(buf))
            strncpy(sv->sdt, buf, sizeof(sv->sdt) - 1);
        else
            printf("  -> Giu nguyen gia tri cu.\n");
    }

    /* GPA */
    printf("GPA [%.2f]: ", sv->gpa);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        float newGpa;
        if (isValidGPA(buf, &newGpa))
            sv->gpa = newGpa;
        else
            printf("  -> Giu nguyen gia tri cu.\n");
    }

    printf("[OK] Da cap nhat thong tin sinh vien '%s'.\n", sv->mssv);
    printf("\nThong tin moi:\n");
    inThongTinSV(sv);
}

/* ================================================================
   8. XUAT FILE DANH SACH SINH VIEN THEO LOP
   ================================================================ */

void chucNang_XuatFileSVTheoLop(HashMapLop *hmLop)
{
    char maLop[10];
    printf("Nhap ma lop can xuat file: ");
    if (scanf("%9s", maLop) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    Lop *lop = hmLopTimKiem(hmLop, maLop);
    if (!lop) {
        printf("[LOI] Khong tim thay lop '%s'.\n", maLop);
        return;
    }

    char tenFile[30];
    snprintf(tenFile, sizeof(tenFile), "sv_lop_%s.csv", maLop);

    FILE *f = fopen(tenFile, "w");
    if (!f) {
        printf("[LOI] Khong mo duoc file de ghi: %s\n", tenFile);
        return;
    }

    fprintf(f, "MSSV,Ho va ten,Ngay sinh,Email,SDT,Ma lop,GPA\n");

    const SinhVien *sv = lop->danhSachSV;
    int soLuong = 0;
    while (sv) {
        fprintf(f, "%s,%s,%s,%s,%s,%s,%.2f\n",
                sv->mssv, sv->hoVaTen, sv->ngaySinh,
                sv->email, sv->sdt, sv->maLop, sv->gpa);
        soLuong++;
        sv = sv->next;
    }

    fclose(f);
    printf("[OK] Da xuat %d sinh vien cua lop '%s' ra file '%s'.\n",
           soLuong, maLop, tenFile);
}

/* ================================================================
   9. LUU DU LIEU RA FILE
   ================================================================ */

void chucNang_LuuFile(const Lop *headLop)
{
    luuSVRaFile(headLop,  "danh_sach_sinh_vien.csv");
    luuLopRaFile(headLop, "danh_sach_lop.csv");
    printf("[OK] Da luu xong du lieu ra file.\n");
}