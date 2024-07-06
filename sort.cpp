#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <memory.h>

#include "sort.h"

static void SwapBytes(void* a, void* b, size_t size);
static void* Partition(void* left, void* right, size_t elSize,  Compare_t* CompareFunc);

//-----------------------------------------------------------------------------------

void Sort(void* left, void* right, size_t elSize, Compare_t* CompareFunc) {
    assert(left        != nullptr);
    assert(right       != nullptr);
    assert(CompareFunc != nullptr);

    if (left < right) {
        void* mid = Partition(left, right, elSize, CompareFunc);

        Sort(left               , (char*)mid-elSize, elSize, CompareFunc);
        Sort((char*)mid + elSize, right            , elSize, CompareFunc);
    }
}

//------------------------------------------------------------------------------------

static void* Partition(void* left, void* right, size_t elSize,  Compare_t* CompareFunc) {
    assert(left        != nullptr);
    assert(right       != nullptr);
    assert(CompareFunc != nullptr);

    void* pivot = right;
    void* store = left;

    while (left < right) {
        if (!CompareFunc(left, pivot)) {
            SwapBytes(store, left, elSize);
            store = (char*)store + elSize;
        }
        left = (char*)left + elSize;
    }

    SwapBytes(right, store, elSize);

    return store;
}



static void SwapBytes(void* a, void* b, size_t size) {
    assert(a != nullptr);
    assert(b != nullptr);
    // assert(a != b);

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
