#pragma once

#include<stdio.h>

int hash(char* str, int baseNumber, int tableSize);

int count_collisions(char** str_array, int array_size, int baseNumber, int tableSize);

