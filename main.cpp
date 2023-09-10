#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>

#include <string.h>

#include "sort.h"
#include "strcmp.h"

int main() {
    // FILE* fileToRead  = fopen("poem", "r" );
    FILE* fileToRead  = fopen("input", "r");
    assert(fileToRead  != nullptr);
    FILE* fileToWrite = fopen("sorted", "w");
    assert(fileToWrite != nullptr);

    //
    fseek(fileToRead, 0, SEEK_END);
    ssize_t fileSize = ftell(fileToRead) + 2;
    fseek(fileToRead, 0, SEEK_SET);
    // ^ file size

    //
    char* buf = (char*)calloc((size_t)fileSize, sizeof(char));
    // ^ hold file chars

    //
    fread(buf, sizeof(char), (size_t)fileSize, fileToRead);
    *(buf + fileSize - 1 - 1) = '\n';
    *(buf + fileSize - 1)     = '\0';

    // ^ read file

    //
    char* iter = buf;
    size_t lines = 0;

    while (iter != buf + fileSize) {
        if (*iter == '\n') {
            lines++;
            *iter = '\0';
        }
        iter++;
    }
    iter = buf;
    // ^ count lines

    //
    char** text = (char**)calloc(lines+1, sizeof(char*));
    // ^ hold all strings array

    //
    char** fillText = text;
    bool nLinePrev = true;

    while (iter != buf + fileSize) {
        if (nLinePrev) {
            *fillText = iter;
            fillText++;
        }

        if (*iter == '\0') {
            nLinePrev = true;
        } else {
            nLinePrev = false;
        }

        iter++;
    }
    // ^ fill text arr

    Sort(text, lines , sizeof(char*), &Strcmp);
    for (size_t i = 0; i < lines; i++) {
        fprintf(fileToWrite, "%s\n", *(text + i));
    }

    free(buf);
    buf = nullptr;
    free(text);
    text = nullptr;

    return 0;
}
