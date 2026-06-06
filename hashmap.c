#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hashStr(const char *key)
{
    unsigned int hash = 5381;
    int c;
    while ((c = (unsigned char)*key++))
        hash = ((hash << 5) + hash) + c;   /* hash * 33 + c */
    return hash % HASH_SIZE;
}

void hmLopKhoiTao(HashMapLop *hm)
{
	int i;
    for (i = 0; i < HASH_SIZE; i++)
        hm->buckets[i] = NULL;
}

void hmLopThem(HashMapLop *hm, Lop *lop)
{
    unsigned int idx = hashStr(lop->maLop);
    EntryLop *entry = (EntryLop *)malloc(sizeof(EntryLop));
    strncpy(entry->key, lop->maLop, sizeof(entry->key) - 1);
    entry->key[sizeof(entry->key) - 1] = '\0';
    entry->lop  = lop;
    entry->next = hm->buckets[idx];   /* chen vao dau chuoi */
    hm->buckets[idx] = entry;
}

Lop *hmLopTimKiem(HashMapLop *hm, const char *maLop)
{
    unsigned int idx = hashStr(maLop);
    EntryLop *cur = hm->buckets[idx];
    while (cur) {
        if (strcmp(cur->key, maLop) == 0)
            return cur->lop;
        cur = cur->next;
    }
    return NULL;
}

void hmLopXoa(HashMapLop *hm, const char *maLop)
{
    unsigned int idx = hashStr(maLop);
    EntryLop **pp = &hm->buckets[idx];
    while (*pp) {
        if (strcmp((*pp)->key, maLop) == 0) {
            EntryLop *del = *pp;
            *pp = del->next;
            free(del);
            return;
        }
        pp = &(*pp)->next;
    }
}

void hmLopHuy(HashMapLop *hm)
{
	int i;
    for (i = 0; i < HASH_SIZE; i++) {
        EntryLop *cur = hm->buckets[i];
        while (cur) {
            EntryLop *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
        hm->buckets[i] = NULL;
    }
}

void hmSVKhoiTao(HashMapSV *hm)
{
	int i;
    for (i = 0; i < HASH_SIZE; i++)
        hm->buckets[i] = NULL;
}

void hmSVThem(HashMapSV *hm, SinhVien *sv)
{
    unsigned int idx = hashStr(sv->mssv);
    EntrySV *entry = (EntrySV *)malloc(sizeof(EntrySV));
    strncpy(entry->key, sv->mssv, sizeof(entry->key) - 1);
    entry->key[sizeof(entry->key) - 1] = '\0';
    entry->sv   = sv;
    entry->next = hm->buckets[idx];
    hm->buckets[idx] = entry;
}

SinhVien *hmSVTimKiem(HashMapSV *hm, const char *mssv)
{
    unsigned int idx = hashStr(mssv);
    EntrySV *cur = hm->buckets[idx];
    while (cur) {
        if (strcmp(cur->key, mssv) == 0)
            return cur->sv;
        cur = cur->next;
    }
    return NULL;
}

void hmSVXoa(HashMapSV *hm, const char *mssv)
{
    unsigned int idx = hashStr(mssv);
    EntrySV **pp = &hm->buckets[idx];
    while (*pp) {
        if (strcmp((*pp)->key, mssv) == 0) {
            EntrySV *del = *pp;
            *pp = del->next;
            free(del);
            return;
        }
        pp = &(*pp)->next;
    }
}

void hmSVHuy(HashMapSV *hm)
{
	int i;
    for (i = 0; i < HASH_SIZE; i++) {
        EntrySV *cur = hm->buckets[i];
        while (cur) {
            EntrySV *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
        hm->buckets[i] = NULL;
    }
}

