#ifndef STRCMP_H
#define STRCMP_H

/**
 * @brief compare two strings from start
 *
 * @param a pointer to first string
 * @param b pointer to second string
 *
 * @return if a > b: 1 else: 0
*/
int StrCmp(const void* a,const void* b);


/**
 * @brief compare two strings from end (in reverse)
 *
 * @param a pointer to first string
 * @param b pointer to second string
 *
 * @return if a > b: 1 else: 0 (in reverse)
*/
int StrCmpRv(const void* a,const void* b);

#endif // STRCMP_H
