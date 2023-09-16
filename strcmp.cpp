#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "strcmp.h"

int StrCmp(const void* a,const void* b) { //NOTE - careful
    assert(a != nullptr);
    assert(b != nullptr);

    Str A = *(const Str*)a;
    Str B = *(const Str*)b;

    char* strA = A.str;
    char* strB = B.str;

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

int StrCmpRv(const void* a,const void* b) { //NOTE - careful
    assert(a != nullptr);
    assert(b != nullptr);

    Str A = *(const Str*)a;
    Str B = *(const Str*)b;

    char* strA = A.str;
    char* strB = B.str;

    char* endA = strA + A.len;
    char* endB = strB + B.len;

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
