#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <memory.h>

#include "sort.h"

static void SwapBytes(void* a, void* b, size_t size);

void Sort(void* data, size_t size, size_t elSize, Compare_t* CompareFunc) { //FIXME - переписать по qsort
    assert(data        != nullptr);
    assert(CompareFunc != nullptr);

    for (ssize_t sortedEl = (ssize_t)(size - 1); sortedEl >= 0; sortedEl--) {
        for (size_t cur = 0; cur < (size_t)sortedEl; cur++) {
            if (CompareFunc(*(void**)((size_t)data + elSize*cur), *(void**)((size_t)data + elSize*(cur + 1)))) {
                // printf("# %s -> %s\n", *(void**)((size_t)data + elSize*cur), *(void**)((size_t)data + elSize*(cur + 1)));
                SwapBytes((void*)((size_t)data + elSize*cur), (void*)((size_t)data + elSize*(cur + 1)), elSize);
            }

        }
    }
}

static void SwapBytes(void* a, void* b, size_t size) {
    assert(a != nullptr);
    assert(b != nullptr);
    assert(a != b);

    size_t nFullOps = size >> 3; // колво шагов по 8
    size_t trailer = size & 0b111; // оставшиеся 7 байт

    uint8_t* aMove = (uint8_t*)a;
    uint8_t* bMove = (uint8_t*)b;
    for (size_t i = 0; i < nFullOps; i++) {
        uint64_t temp = 0;
        memcpy(&temp, aMove, sizeof(uint64_t));
               memcpy(aMove, bMove, sizeof(uint64_t));
                      memcpy(bMove, &temp, sizeof(uint64_t));
        aMove += sizeof(uint64_t);
        bMove += sizeof(uint64_t);
    }

    if (trailer & 0b100) {
        uint32_t temp = 0;
        memcpy(&temp, aMove, sizeof(uint32_t));
               memcpy(aMove, bMove, sizeof(uint32_t));
                      memcpy(bMove, &temp, sizeof(uint32_t));
        aMove += sizeof(uint32_t);
        bMove += sizeof(uint32_t);
    }
    if (trailer & 0b010) {
        uint16_t temp = 0;
        memcpy(&temp, aMove, sizeof(uint16_t));
               memcpy(aMove, bMove, sizeof(uint16_t));
                      memcpy(bMove, &temp, sizeof(uint16_t));
        aMove += sizeof(uint16_t);
        bMove += sizeof(uint16_t);
    }
    if (trailer & 0b001) {
        uint8_t temp = 0;
        memcpy(&temp, aMove, sizeof(uint8_t));
               memcpy(aMove, bMove, sizeof(uint8_t));
                      memcpy(bMove, &temp, sizeof(uint8_t));
    }
}
