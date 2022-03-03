#pragma once
#include "records.h"

void swap(record* a, record* b);

int partition(record list[], int l, int h);

void QuickSort(record list[], int l, int h, int s);