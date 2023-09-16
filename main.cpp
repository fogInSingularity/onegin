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
    const char* fileNameToRead = "poem";
    FILE* fileToRead  = fopen(fileNameToRead, "r" );
    if (fileToRead == nullptr) {
        printf("# error: cant open file to read: %s\n", fileNameToRead);
        return 0;
    }

    const char* fileNameToWrite = "sorted";
    FILE* fileToWrite = fopen(fileNameToWrite, "w");
    if (fileToWrite == nullptr) {
        printf("# error: cant open file to write: %s\n", fileNameToWrite);
        return 0;
    }

    Data data = {}; // nullify data

    GetData(&data, fileToRead);

    //-------------------------------------------------------------------

    Sort(data.text, data.text + data.nLines - 1, sizeof(Str), &StrCmp);

    PutData(&data, fileToWrite);


    qsort(data.text, data.nLines, sizeof(Str), &StrCmpRv);

    PutData(&data, fileToWrite);


    PutBuf(&data, fileToWrite);

    //-------------------------------------------------------------------

    fclose(fileToRead);
    fileToRead = nullptr;

    fclose(fileToWrite);
    fileToWrite = nullptr;

    FreeData(&data);

    return 0;
}
