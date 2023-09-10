#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <memory.h>

#include "sort.h"

void Sort(void* data, size_t size, size_t elSize, Compare_t* CompareFunc) {
    // for (size_t i = 0; i < size; i++) {
    //     for (size_t j = 0; j < i; j++) {
    //         printf("# i: %lu %p\n", j, *(char**)data + elSize*j);
    //         printf("# j: %lu %p\n", j + 1, *(char**)data + elSize*(j + 1));

    //         // норм голову поломал)
    //         // char* because we determane data size our self
    //         if (CompareFunc(*(char**)data + elSize*j, *(char**)data + elSize*(j + 1))) {
    //             printf("# swap: %s -> %s\n", *(char**)data + elSize*j, *(char**)data + elSize*(j + 1));
    //             SwapBytes(*(char**)data + elSize*j, *(char**)data + elSize*(j + 1), sizeof(char*));
    //         }
    //     }
    // }

    for (ssize_t sortedEl = (size - 1); sortedEl >= 0; sortedEl--) {
        for (size_t cur = 0; cur < sortedEl; cur++) {
            if (CompareFunc(*(void**)((size_t)data + elSize*cur), *(void**)((size_t)data + elSize*(cur + 1))) > 0) {
                // printf("#%lu %lu swap: %s -> %s\n", sortedEl, cur, *(void**)((size_t)data + elSize*cur), *(void**)((size_t)data + elSize*(cur + 1)));
                SwapBytes((void*)((size_t)data + elSize*cur), (void*)((size_t)data + elSize*(cur + 1)), elSize); //FIXME - cringe
            }
        }
    }
}

void SwapBytes(void* a, void* b, size_t size) {
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
