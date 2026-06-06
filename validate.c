#include "validate.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* ================================================================
   HAM TIEN ICH
   ================================================================ */

int laNamNhuan(int nam)
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

int soNgayHopLe(int ngay, int thang, int nam)
{
    int maxNgay[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (thang < 1 || thang > 12) return 0;
    if (thang == 2 && laNamNhuan(nam)) maxNgay[2] = 29;
    return ngay >= 1 && ngay <= maxNgay[thang];
}

/* ================================================================
   KIEM TRA MSSV
   ================================================================ */

int isValidMSSV(const char *mssv)
{
    int i, len;
    if (!mssv || mssv[0] == '\0') {
        printf("  [LOI] MSSV khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(mssv);
    if (len < 1 || len > 7) {
        printf("  [LOI] MSSV phai tu 1 den 7 ky tu (hien tai: %d).\n", len);
        return 0;
    }
    for (i = 0; i < len; i++) {
        char c = mssv[i];
        int isAlpha = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        int isDigit = (c >= '0' && c <= '9');
        if (!isAlpha && !isDigit) {
            printf("  [LOI] MSSV chi duoc chua chu cai va chu so (ky tu loi: '%c').\n", c);
            return 0;
        }
    }
    return 1;
}

/* ================================================================
   KIEM TRA HO VA TEN
   ================================================================ */

int isValidHoVaTen(const char *ten)
{
    int i, len, coKyTuHopLe;
    if (!ten || ten[0] == '\0') {
        printf("  [LOI] Ho va ten khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(ten);
    if (len < 2) {
        printf("  [LOI] Ho va ten qua ngan (toi thieu 2 ky tu).\n");
        return 0;
    }
    if (len > 99) {
        printf("  [LOI] Ho va ten qua dai (toi da 99 ky tu).\n");
        return 0;
    }
    /* Kiem tra khong chi toan khoang trang */
    coKyTuHopLe = 0;
    for (i = 0; i < len; i++) {
        if (ten[i] != ' ') { coKyTuHopLe = 1; break; }
    }
    if (!coKyTuHopLe) {
        printf("  [LOI] Ho va ten khong hop le (chi co khoang trang).\n");
        return 0;
    }
    /* Kiem tra khong co 2 khoang trang lien tiep */
    for (i = 0; i < len - 1; i++) {
        if (ten[i] == ' ' && ten[i+1] == ' ') {
            printf("  [LOI] Ho va ten khong duoc co 2 khoang trang lien tiep.\n");
            return 0;
        }
    }
    /* Khong bat dau hoac ket thuc bang khoang trang */
    if (ten[0] == ' ' || ten[len-1] == ' ') {
        printf("  [LOI] Ho va ten khong duoc bat dau hoac ket thuc bang khoang trang.\n");
        return 0;
    }
    return 1;
}

/* ================================================================
   KIEM TRA NGAY SINH
   ================================================================ */

int isValidNgaySinh(const char *ngay)
{
    int dd, mm, yyyy;
    int len;
    if (!ngay || ngay[0] == '\0') {
        printf("  [LOI] Ngay sinh khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(ngay);
    if (len != 10) {
        printf("  [LOI] Ngay sinh phai dung dinh dang DD/MM/YYYY (vi du: 01/01/2000).\n");
        return 0;
    }
    /* Kiem tra vi tri dau '/' */
    if (ngay[2] != '/' || ngay[5] != '/') {
        printf("  [LOI] Ngay sinh phai dung dinh dang DD/MM/YYYY.\n");
        return 0;
    }
    /* Kiem tra cac vi tri con lai la chu so */
    {
        int pos[] = {0,1,3,4,6,7,8,9};
        int i;
        for (i = 0; i < 8; i++) {
            if (ngay[pos[i]] < '0' || ngay[pos[i]] > '9') {
                printf("  [LOI] Ngay sinh chua ky tu khong phai chu so tai vi tri %d.\n", pos[i]+1);
                return 0;
            }
        }
    }
    dd   = (ngay[0]-'0')*10 + (ngay[1]-'0');
    mm   = (ngay[3]-'0')*10 + (ngay[4]-'0');
    yyyy = (ngay[6]-'0')*1000 + (ngay[7]-'0')*100 + (ngay[8]-'0')*10 + (ngay[9]-'0');

    if (yyyy < 1900 || yyyy > 2099) {
        printf("  [LOI] Nam sinh phai trong khoang 1900-2099 (nhap: %d).\n", yyyy);
        return 0;
    }
    if (mm < 1 || mm > 12) {
        printf("  [LOI] Thang phai tu 01 den 12 (nhap: %02d).\n", mm);
        return 0;
    }
    if (!soNgayHopLe(dd, mm, yyyy)) {
        printf("  [LOI] Ngay %02d khong hop le voi thang %02d nam %04d.\n", dd, mm, yyyy);
        return 0;
    }
    return 1;
}

/* ================================================================
   KIEM TRA EMAIL
   ================================================================ */

int isValidEmail(const char *email)
{
    int i, len, posAt, demAt, posDot;
    if (!email || email[0] == '\0') {
        printf("  [LOI] Email khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(email);
    if (len > 99) {
        printf("  [LOI] Email qua dai (toi da 99 ky tu).\n");
        return 0;
    }
    /* Dem so ky tu '@' */
    demAt = 0; posAt = -1;
    for (i = 0; i < len; i++) {
        if (email[i] == '@') { demAt++; posAt = i; }
    }
    if (demAt == 0) {
        printf("  [LOI] Email thieu ky tu '@'.\n");
        return 0;
    }
    if (demAt > 1) {
        printf("  [LOI] Email chi duoc co dung mot ky tu '@'.\n");
        return 0;
    }
    /* Phan truoc '@' khong duoc rong */
    if (posAt == 0) {
        printf("  [LOI] Email khong hop le: phan truoc '@' bi trong.\n");
        return 0;
    }
    /* Phan sau '@' phai co it nhat 'x.y' */
    if (posAt >= len - 3) {
        printf("  [LOI] Email khong hop le: phan sau '@' qua ngan.\n");
        return 0;
    }
    /* Tim dau '.' trong phan sau '@' */
    posDot = -1;
    for (i = posAt + 1; i < len; i++) {
        if (email[i] == '.') { posDot = i; }
    }
    if (posDot == -1) {
        printf("  [LOI] Email khong hop le: phan domain thieu dau '.'.\n");
        return 0;
    }
    if (posDot == posAt + 1) {
        printf("  [LOI] Email khong hop le: dau '.' ngay sau '@'.\n");
        return 0;
    }
    if (posDot == len - 1) {
        printf("  [LOI] Email khong hop le: dau '.' o cuoi.\n");
        return 0;
    }
    /* Khong co khoang trang trong email */
    for (i = 0; i < len; i++) {
        if (email[i] == ' ') {
            printf("  [LOI] Email khong duoc chua khoang trang.\n");
            return 0;
        }
    }
    return 1;
}

/* ================================================================
   KIEM TRA SO DIEN THOAI
   ================================================================ */

int isValidSDT(const char *sdt)
{
    int i, soDigit, batDau;
    const char *p;
    if (!sdt || sdt[0] == '\0') {
        printf("  [LOI] So dien thoai khong duoc de trong.\n");
        return 0;
    }
    p = sdt;
    /* Bo qua dau '+' neu co */
    if (p[0] == '+') p++;

    /* Dem va kiem tra toan chu so */
    soDigit = 0;
    for (i = 0; p[i] != '\0'; i++) {
        if (p[i] < '0' || p[i] > '9') {
            printf("  [LOI] So dien thoai chi duoc chua chu so va dau '+' (ky tu loi: '%c').\n", p[i]);
            return 0;
        }
        soDigit++;
    }

    if (soDigit < 9 || soDigit > 12) {
        printf("  [LOI] So dien thoai phai co 9-12 chu so (hien tai: %d chu so).\n", soDigit);
        return 0;
    }

    /* Kiem tra dau so Viet Nam */
    batDau = 0;
    if (sdt[0] == '0' && soDigit == 10) batDau = 1;          /* 0xxx: 10 so */
    if (sdt[0] == '+' && p[0] == '8' && p[1] == '4') batDau = 1; /* +84xxx */
    if (sdt[0] == '8' && sdt[1] == '4' && soDigit == 11) batDau = 1; /* 84xxx: 11 so */
    /* Cho phep so quoc te khac (9 hoac 12 chu so) */
    if (soDigit == 9 || soDigit == 12) batDau = 1;

    if (!batDau) {
        printf("  [LOI] So dien thoai khong dung dinh dang Viet Nam.\n");
        printf("        (VD: 0912345678  hoac  +84912345678)\n");
        return 0;
    }
    return 1;
}

/* ================================================================
   KIEM TRA MA LOP
   ================================================================ */

int isValidMaLop(const char *maLop)
{
    int i, len;
    if (!maLop || maLop[0] == '\0') {
        printf("  [LOI] Ma lop khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(maLop);
    if (len < 1 || len > 4) {
        printf("  [LOI] Ma lop phai tu 1 den 4 ky tu (hien tai: %d).\n", len);
        return 0;
    }
    for (i = 0; i < len; i++) {
        char c = maLop[i];
        int isAlpha = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        int isDigit = (c >= '0' && c <= '9');
        if (!isAlpha && !isDigit) {
            printf("  [LOI] Ma lop chi duoc chua chu cai va chu so (ky tu loi: '%c').\n", c);
            return 0;
        }
    }
    return 1;
}

/* ================================================================
   KIEM TRA GPA
   ================================================================ */

int isValidGPA(const char *input, float *out)
{
    char *endPtr;
    float val;
    int i, len;
    if (!input || input[0] == '\0') {
        printf("  [LOI] GPA khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(input);
    /* Kiem tra chuoi chi chua chu so, dau cham, hoac dau tru o dau */
    for (i = 0; i < len; i++) {
        char c = input[i];
        if (c == '-' && i == 0) continue;   /* cho phep dau tru de detect am */
        if (c == '.') continue;
        if (c < '0' || c > '9') {
            printf("  [LOI] GPA khong hop le: chua ky tu '%c'. Chi nhap so thuc.\n", c);
            return 0;
        }
    }
    val = (float)strtod(input, &endPtr);
    /* Neu endPtr khong tien ve cuoi chuoi -> co ky tu la */
    if (*endPtr != '\0' && *endPtr != '\n') {
        printf("  [LOI] GPA khong phai so hop le.\n");
        return 0;
    }
    if (val < 0.0f) {
        printf("  [LOI] GPA khong duoc am (nhap: %.2f).\n", val);
        return 0;
    }
    if (val > 4.0f) {
        printf("  [LOI] GPA khong duoc vuot qua 4.0 (nhap: %.2f).\n", val);
        return 0;
    }
    *out = val;
    return 1;
}
