#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"


Lop layThongTinLop(FILE *file)
{
    Lop c;
    char temp[208];
    if (!fgets(temp, sizeof(temp), file)) {
        /* tra ve lop rong neu doc that bai */
        memset(&c, 0, sizeof(c));
        return c;
    }
    temp[strcspn(temp, "\n")] = '\0';

    char *token;
    token = strtok(temp, ",");
    if (!token) { memset(&c, 0, sizeof(c)); return c; }
    strncpy(c.maLop, token, sizeof(c.maLop) - 1);
    c.maLop[sizeof(c.maLop)-1] = '\0';

    token = strtok(NULL, ",");
    strncpy(c.tenLop, token ? token : "", sizeof(c.tenLop) - 1);

    token = strtok(NULL, ",");
    strncpy(c.chuNhiemLop, token ? token : "", sizeof(c.chuNhiemLop) - 1);

    token = strtok(NULL, ",");
    c.soLuongSinhVien = token ? atoi(token) : 0;

    c.danhSachSV = NULL;
    c.tailSV     = NULL;
    c.next       = NULL;
    c.prev       = NULL;
    return c;
}

SinhVien layThongTinSinhVien(FILE *file)
{
    SinhVien sv;
    char temp[300];
    if (!fgets(temp, sizeof(temp), file)) {
        memset(&sv, 0, sizeof(sv));
        return sv;
    }
    temp[strcspn(temp, "\n")] = '\0';

    char *token;
    token = strtok(temp, ",");
    strncpy(sv.mssv, token ? token : "", sizeof(sv.mssv) - 1);
    sv.mssv[sizeof(sv.mssv)-1] = '\0';

    token = strtok(NULL, ",");
    strncpy(sv.hoVaTen, token ? token : "", sizeof(sv.hoVaTen) - 1);
    sv.hoVaTen[sizeof(sv.hoVaTen)-1] = '\0';

    token = strtok(NULL, ",");
    strncpy(sv.ngaySinh, token ? token : "", sizeof(sv.ngaySinh) - 1);
    sv.ngaySinh[sizeof(sv.ngaySinh)-1] = '\0';

    token = strtok(NULL, ",");
    strncpy(sv.email, token ? token : "", sizeof(sv.email) - 1);
    sv.email[sizeof(sv.email)-1] = '\0';

    token = strtok(NULL, ",");
    /* bo qua 4 ky tu dau neu la ma vung quoc te (+84...) */
    if (token) {
        const char *src = (token[0] == '+') ? token + 4 : token;
        strncpy(sv.sdt, src, sizeof(sv.sdt) - 1);
    } else sv.sdt[0] = '\0';
    sv.sdt[sizeof(sv.sdt)-1] = '\0';

    token = strtok(NULL, ",");
    strncpy(sv.maLop, token ? token : "", sizeof(sv.maLop) - 1);
    sv.maLop[sizeof(sv.maLop)-1] = '\0';

    token = strtok(NULL, ",");
    sv.gpa = token ? atof(token) : 0.0f;

    sv.next = NULL;
    sv.prev = NULL;
    return sv;
}

Lop *taoNodeLop(Lop c)
{
    Lop *node = (Lop *)malloc(sizeof(Lop));
    if (!node) return NULL;
    *node = c;
    return node;
}

SinhVien *taoNodeSinhVien(SinhVien c)
{
    SinhVien *node = (SinhVien *)malloc(sizeof(SinhVien));
    if (!node) return NULL;
    *node = c;
    return node;
}

/* Them node (da cap phat) vao duoi linked list lop */
void themVaoLLLop(Lop **head, Lop **tail, Lop *newNode)
{
    if (!newNode) return;
    newNode->next = NULL;
    newNode->prev = *tail;
    if (*tail) (*tail)->next = newNode;
    else       *head = newNode;
    *tail = newNode;
}

/* Them node (da cap phat) vao duoi linked list sinh vien */
void themVaoLLSV(SinhVien **head, SinhVien **tail, SinhVien *newNode)
{
    if (!newNode) return;
    newNode->next = NULL;
    newNode->prev = *tail;
    if (*tail) (*tail)->next = newNode;
    else       *head = newNode;
    *tail = newNode;
}

void xoaSinhVien(SinhVien **head, SinhVien **tail, SinhVien *node)
{
    if (!node) return;
    if (node->prev) node->prev->next = node->next; else *head = node->next;
    if (node->next) node->next->prev = node->prev; else *tail = node->prev;
    free(node);
}

void xoaLop(Lop **head, Lop **tail, Lop *node)
{
    if (!node) return;
    SinhVien *sv = node->danhSachSV;
    while (sv) { SinhVien *tmp = sv->next; free(sv); sv = tmp; }
    if (node->prev) node->prev->next = node->next; else *head = node->next;
    if (node->next) node->next->prev = node->prev; else *tail = node->prev;
    free(node);
}

/* Ghi de file danh_sach_sinh_vien.csv tu linked list */
void luuSVRaFile(const Lop *headLop, const char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f) {
        printf("[LOI] Khong mo duoc file de ghi: %s\n", filePath);
        return;
    }
 
    /* Dong tieu de giong file goc */
    fprintf(f, "MSSV,Ho va ten,Ngay sinh,Email,SDT,Ma lop,GPA\n");
 
    const Lop *lop = headLop;
    while (lop) {
        const SinhVien *sv = lop->danhSachSV;
        while (sv) {
            fprintf(f, "%s,%s,%s,%s,%s,%s,%.2f\n",
                    sv->mssv,
                    sv->hoVaTen,
                    sv->ngaySinh,
                    sv->email,
                    sv->sdt,
                    sv->maLop,
                    sv->gpa);
            sv = sv->next;
        }
        lop = lop->next;
    }
 
    fclose(f);
    printf("[OK] Da ghi de file sinh vien: %s\n", filePath);
}

/* Ghi de file danh_sach_lop.csv tu linked list */
void luuLopRaFile(const Lop *headLop, const char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f) {
        printf("[LOI] Khong mo duoc file de ghi: %s\n", filePath);
        return;
    }
 
    /* Dong tieu de giong file goc */
    fprintf(f, "Ma lop,Ten lop,Chu nhiem lop,So luong sinh vien\n");
 
    const Lop *lop = headLop;
    while (lop) {
        fprintf(f, "%s,%s,%s,%d\n",
                lop->maLop,
                lop->tenLop,
                lop->chuNhiemLop,
                lop->soLuongSinhVien);
        lop = lop->next;
    }
 
    fclose(f);
    printf("[OK] Da ghi de file lop: %s\n", filePath);
}
