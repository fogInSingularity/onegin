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

    // Data data = {
    //     nullptr,
    //     nullptr,
    //     0,
    //     0,
    // };

    const size_t fileSize = (size_t)FileSize(fileToRead) + 2;

    char* buf = (char*)calloc(fileSize, sizeof(char)); // hold file chars

    FileRead(buf, fileSize, fileToRead);

    const size_t lines = CountLines(buf, fileSize);

    SwapN(buf, fileSize);

    char** text = (char**)calloc(lines+1, sizeof(char*));

    FillText(text, buf, fileSize);

    Sort(text, lines , sizeof(char*), &StrCmpRv);

    PrintText(fileToWrite, lines, text);

    free(buf);
    buf = nullptr;
    free(text);
    text = nullptr;

    return 0;
}
