#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "strcmp.h"

static bool IsValid(char c);

int StrCmp(void* a, void* b) {
    assert(a != nullptr);
    assert(b != nullptr);

    char* strA = (char*)a;
    char* strB = (char*)b;

    while (*strA != '\0' && *strB != '\0') {
        while (!IsValid(*strA)) {
            strA++;
        }
        while (!IsValid(*strB)) {
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

int StrCmpRv(void* a, void* b) { //FIXME - написать реверс
    assert(a != nullptr);
    assert(b != nullptr);

    char* strA = (char*)a;
    char* strB = (char*)b;

    char* endA = strA + strlen(strA) - 1;
    char* endB = strB + strlen(strB) - 1;

    while (strA < endA && strB < endB) { //FIXME - not check when str == end
        while (!IsValid(*endA) && strA < endA) { // был валид от strA и из-за этого сорт был карявый
            endA--;
        }

        while (!IsValid(*endB) && strB < endB) {
            endB--;
        }

        if (*endA != *endB) {
            // printf("# return %d\n", *endA - *endB);
            // printf("# %c -> %c\n", *strA, *strB);
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

static bool IsValid(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    } else if (c >= 'A' && c <= 'Z') {
        return true;
    } else if (c >= 'a' && c <= 'z') {
        return true;
    } else if (c == '\0') {
        return true;
    } else {
        return false;
    }
}
