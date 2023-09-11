#ifndef SORT_H
#define SORT_H

#include <stddef.h>

typedef int Compare_t(void* a, void* b);

void Sort(void* data, size_t size, size_t elSize, Compare_t* CompareFunc);

#endif // SORT_H
