#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "hashmap.h"
#include "linkedlist.h"
#include "inRaManHinh.h"
#include "napDuLieu.h"
#include "chucNang.h"

int main(void)
{
    /* --- Khoi tao cac cau truc --- */
    Lop        *headLop = NULL, *tailLop = NULL;
    HashMapLop  hmLop;
    HashMapSV   hmSV;
    int         luaChon;

    hmLopKhoiTao(&hmLop);
    hmSVKhoiTao(&hmSV);

    /* --- Kiem tra file truoc khi nap --- */
    FILE *fileLop = fopen("danh_sach_lop.csv", "r");
    FILE *fileSV  = fopen("danh_sach_sinh_vien.csv", "r");

    if (fileLop && fileSV) {
        fclose(fileLop);
        fclose(fileSV);
        napDuLieu("danh_sach_lop.csv", "danh_sach_sinh_vien.csv",
                  &headLop, &tailLop, &hmLop, &hmSV);
    } else {
        if (fileLop) fclose(fileLop);
        if (fileSV)  fclose(fileSV);
        printf("[INFO] Khong tim thay file CSV. Bat dau voi du lieu trong.\n");
    }

    /* --- Vong lap chinh --- */
    while (1) {
        inMenu();

        if (scanf("%d", &luaChon) != 1) {
            xoaBuffer();
            printf("[LOI] Vui long nhap so.\n");
            continue;
        }
        xoaBuffer();

        switch (luaChon) {
        case 1:
            chucNang_InToanBoLop(headLop);
            break;
        case 2:
            chucNang_InSVTheoLop(&hmLop);
            break;
        case 3:
            chucNang_TimSVTheoMSSV(&hmSV);
            break;
        case 4:
            chucNang_TimSVTheoTen(headLop);
            break;
        case 5:
            chucNang_ThemSinhVien(&headLop, &tailLop, &hmLop, &hmSV);
            break;
        case 6:
            chucNang_XoaSinhVien(&headLop, &tailLop, &hmLop, &hmSV);
            break;
        case 7:
            chucNang_CapNhatSV(&hmSV);
            break;
        case 8:
            chucNang_LuuFile(headLop);
            break;
        case 0:
            chucNang_LuuFile(headLop);
            printf("Tam biet!\n");
            /* Giai phong bo nho truoc khi thoat */
            hmLopHuy(&hmLop);
            hmSVHuy(&hmSV);
            while (headLop) {
                Lop *tmp = headLop->next;
                /* SinhVien nodes da duoc free boi hmSVHuy, chi free Lop */
                free(headLop);
                headLop = tmp;
            }
            return 0;
        default:
            printf("[LOI] Lua chon khong hop le. Vui long chon lai (0-8).\n");
            break;
        }
    }
}
