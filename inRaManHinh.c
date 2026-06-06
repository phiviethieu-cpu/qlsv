#include <stdio.h>
#include "types.h"

#define HASH_SIZE 10007

void inThongTinSV(const SinhVien *sv)
{
    if (!sv) { printf("  [Khong tim thay]\n"); return; }
    printf("  MSSV    : %s\n", sv->mssv);
    printf("  Ho va ten: %s\n", sv->hoVaTen);
    printf("  Ngay sinh: %s\n", sv->ngaySinh);
    printf("  Email   : %s\n", sv->email);
    printf("  SDT     : %s\n", sv->sdt);
    printf("  Ma lop  : %s\n", sv->maLop);
    printf("  GPA     : %.2f\n", sv->gpa);
}

void inDanhSachLop(const Lop *lop)
{
    if (!lop) { printf("[Khong tim thay lop]\n"); return; }
    printf("=== Lop: %s | %s | CN: %s ===\n",
           lop->maLop, lop->tenLop, lop->chuNhiemLop);
    const SinhVien *sv = lop->danhSachSV;
    int i = 1;
    while (sv) {
        printf("  %d. [%s] %s - GPA: %.2f\n", i++, sv->mssv, sv->hoVaTen, sv->gpa);
        sv = sv->next;
    }
    if (i == 1) printf("  (Chua co sinh vien)\n");
}

void inToanBoLop(const Lop *headLop)
{
    const Lop *lop = headLop;
    while (lop) {
        inDanhSachLop(lop);
        printf("\n");
        lop = lop->next;
    }
}
