#ifndef SORT_H
#define SORT_H

#include <stddef.h>


/// @brief alias for compare function
typedef int Compare_t(void* a, void* b);

/**
 * @brief sorts array
 *
 * @param left left side off array
 * @param right right size off array
 * @param elSize size of element
 * @param CompareFunc comparator function
*/
void Sort(void* left, void* right, size_t elSize, Compare_t* CompareFunc);

#endif // SORT_H
