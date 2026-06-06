#include "napDuLieu.h"
#include "hashmap.h"
#include "types.h"
#include "linkedlist.h"


//   NAP DU LIEU TU FILE
// 
//   Luong xu ly:
//     1) Doc file lop -> tao node Lop -> them vao LL lop + hmLop
//     2) Doc file sinh vien -> tao node SinhVien -> them vao hmSV
//        -> tra cuu lop qua hmLop -> gan vao LL sinh vien cua lop do

void napDuLieu(const char *fileLopPath, const char *fileSVPath,
               Lop **headLop, Lop **tailLop,
               HashMapLop *hmLop, HashMapSV *hmSV)
{
    /* --- Doc file lop --- */
    FILE *fLop = fopen(fileLopPath, "r");
    if (!fLop) {
        printf("[LOI] Khong mo duoc file: %s\n", fileLopPath);
    } else {
        fscanf(fLop, "%*[^\n]\n"); /* bo dong tieu de */
        while (!feof(fLop)) { //feof: kiem tra da chay toi cuoi file hay chua
            Lop tmp = layThongTinLop(fLop);
            if (tmp.maLop[0] == '\0') continue; /* dong rong */
            Lop *node = taoNodeLop(tmp);
            if (!node) continue;
            themVaoLLLop(headLop, tailLop, node);
            hmLopThem(hmLop, node);
        }
        fclose(fLop);
        printf("[OK] Da nap file lop: %s\n", fileLopPath);
    }

    /* --- Doc file sinh vien --- */
    FILE *fSV = fopen(fileSVPath, "r");
    if (!fSV) {
        printf("[LOI] Khong mo duoc file: %s\n", fileSVPath);
    } else {
        fscanf(fSV, "%*[^\n]\n"); /* bo dong tieu de */
        while (!feof(fSV)) {
            SinhVien tmp = layThongTinSinhVien(fSV);
            if (tmp.mssv[0] == '\0') continue;
            SinhVien *node = taoNodeSinhVien(tmp);
            if (!node) continue;

            /* Gan vao LL sinh vien cua lop tuong ung */
            Lop *lop = hmLopTimKiem(hmLop, node->maLop);
            if (lop) {
                themVaoLLSV(&lop->danhSachSV, &lop->tailSV, node);
            } else {
                /* Lop chua ton tai: van luu vao hmSV nhung khong gan vao lop */
                printf("[CANH BAO] Khong tim thay lop '%s' cho SV %s\n",
                       node->maLop, node->mssv);
            }
            hmSVThem(hmSV, node);
        }
        fclose(fSV);
        printf("[OK] Da nap file sinh vien: %s\n", fileSVPath);
    }
}
