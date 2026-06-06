#ifndef DATA_H
#define DATA_H

#include "types.h"

/* --- Nap du lieu --- */
void napDuLieu(const char *fileLopPath, const char *fileSVPath,
               Lop **headLop, Lop **tailLop,
               HashMapLop *hmLop, HashMapSV *hmSV);
               
#endif
