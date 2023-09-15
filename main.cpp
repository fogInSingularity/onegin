#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "sort.h"
#include "strcmp.h"
#include "utils.h"

int main() {
    FILE* fileToRead  = fopen("poem", "r" );
    // FILE* fileToRead  = fopen("input", "r");
    if (fileToRead == nullptr) {
        printf("# error: cant open file to read\n");
        return 0;
    }

    FILE* fileToWrite = fopen("sorted", "w");
    if (fileToWrite == nullptr) {
        printf("# error: cant open file to write\n");
        return 0;
    }

    Data data = {
        nullptr,
        0,
        nullptr,
        0,
    };

    GetData(&data, fileToRead);

    Sort(data.text, data.text + data.nLines - 1, sizeof(char*), &StrCmp);

    PutData(&data, fileToWrite);

    fprintf(fileToWrite, "\n-----------------------------------------------\n\n\n");

    Sort(data.text, data.text + data.nLines - 1 , sizeof(char*), &StrCmpRv);

    PutData(&data, fileToWrite);

    fprintf(fileToWrite, "\n-----------------------------------------------\n\n\n");

    Sort(data.text, data.text + data.nLines - 1 , sizeof(char*), &StrCmpDef);

    PutData(&data, fileToWrite);

    FreeData(&data);

    return 0;
}
