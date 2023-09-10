#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>

#include "strcmp.h"

int Strcmp(void* a, void* b) {
    assert(a != nullptr);
    assert(b != nullptr);

    char* strA = (char*)a;
    char* strB = (char*)b;

    // printf("#       no drop\n");
    while (*strA != '\n' || *strB != '\n') {
        while (!IsValid(*strA)) {
            strA++;
        }
        while (!IsValid(*strB)) {
            strB++;
        }

        if (*strA != *strB) {
            return *strA - *strB;
        }
    }


    return 0;
}

bool IsValid(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    } else if (c >= 'A' && c <= 'Z') {
        return true;
    } else if (c >= 'a' && c <= 'z') {
        return true;
    } else {
        return false;
    }
}
