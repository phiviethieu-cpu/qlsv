#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"



/* --- Linked list --- */
Lop     layThongTinLop(FILE *file);
SinhVien layThongTinSinhVien(FILE *file);
Lop    *taoNodeLop(Lop c);
SinhVien *taoNodeSinhVien(SinhVien c);
void    themVaoLLLop(Lop **head, Lop **tail, Lop *newNode);
void    themVaoLLSV(SinhVien **head, SinhVien **tail, SinhVien *newNode);
void    xoaSinhVien(SinhVien **head, SinhVien **tail, SinhVien *node);
void    xoaLop(Lop **head, Lop **tail, Lop *node);
void luuSVRaFile(const Lop *headLop, const char *filePath);
void luuLopRaFile(const Lop *headLop, const char *filePath);

#endif
