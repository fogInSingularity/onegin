#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "strcmp.h"

int StrCmp(void* a, void* b) { //NOTE - careful
    assert(a != nullptr);
    assert(b != nullptr);

    char* strA = *(char**)a;
    char* strB = *(char**)b;

    while (*strA != '\0' && *strB != '\0') {
        while (!isalpha(*strA)) {
            strA++;
        }
        while (!isalpha(*strB)) {
            strB++;
        }

        if (*strA != *strB)
            return (*strA - *strB > 0) ? 1 : 0;

        if (*strA != '\0')
            strA++;
        if (*strB != '\0')
            strB++;
    }

    return 0;
}

int StrCmpRv(void* a, void* b) { //NOTE - careful
    assert(a != nullptr);
    assert(b != nullptr);

    char* strA = *(char**)a;
    char* strB = *(char**)b;

    char* endA = strA + strlen(strA);
    char* endB = strB + strlen(strB);

    while (strA < endA && strB < endB) {
        while (!isalpha(*endA) && strA < endA) {
            endA--;
        }

        while (!isalpha(*endB) && strB < endB) {
            endB--;
        }

        if (*endA != *endB) {
            return (*endA - *endB > 0) ? 1 : 0;
        }

        if (strA < endA) {
            endA--;
        }

        if (strB < endB) {
            endB--;
        }
    }

    return 0;
}

int StrCmpDef(void* a, void* b) {
    return (*(size_t*)a > *(size_t*)b) ? 1 : 0;
}
