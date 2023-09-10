#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>

#include "sort.h"
#include "strcmp.h"

int main() {
    // FILE* fileToRead  = fopen("poem", "r");
    FILE* fileToRead  = fopen("input", "r");
    assert(fileToRead  != nullptr);
    FILE* fileToWrite = fopen("sorted", "w");
    assert(fileToWrite != nullptr);

    // FILE* fileDebug = fopen("debug", "w");
    // assert(fileDebug != nullptr);
    // ^ open all files

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

    while (*iter != '\0') {
        lines += (*iter == '\n');
    
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

    while (*iter != '\0') {
        if (nLinePrev) {
            *fillText = iter;
            fillText++;
        }

        if (*iter == '\n') {
            nLinePrev = true;
        } else {
            nLinePrev = false;
        }

        iter++;
    }
    // ^ fill text arr

    Sort(text, lines + 1, sizeof(char*), &Strcmp);
    // for (size_t i = 0; i < lines; i++) {
    //     for(size_t j = 0; *(*(text + i) + j) != '\n'; j++) {
    //         putchar(*(*(text + i) + j));
    //     }
    //     putchar('\n');
    // }


    // fillText = text;
    // for (size_t i = 0; i < lines + 1; i++) {
    //     fprintf(fileDebug, "%p\n", *fillText);
    //     fillText++;
    // }

    // printf("%lu\n", lines);
    // fprintf(fileToWrite, "%s", buf);

    // printf("\n\nDROPD\n\n\n");

    free(buf);
    buf = nullptr;
    free(text);
    text = nullptr;

    return 0;
}
