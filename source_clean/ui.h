#ifndef UI_H
#define UI_H

#include "restaurant.h"

void runUI();

int menuGiaoDien(const char *options[], int optionCount);

void xoaMonAn(Table *tableList);

void inHoaDon(Table *tableList);

#endif
