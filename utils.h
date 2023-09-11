#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

struct Data {
    char* buf;
    size_t bufSize;

    char** text;
    size_t nLines;
};

void GetData(Data* data, FILE* file);

void PutData(Data* data, FILE* file);

void PutDataRv(Data* data, FILE* file);

#endif
