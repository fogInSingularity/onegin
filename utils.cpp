#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>

#include "utils.h"

ssize_t FileSize(FILE* file) {
    assert(file != nullptr);

    fseek(file, 0, SEEK_END);

    ssize_t size = ftell(file);

    fseek(file, 0, SEEK_SET);

    return size;
}

void FileRead(char* buf, size_t fileSize, FILE* fileToRead) {
    assert(buf        != nullptr);
    assert(fileToRead != nullptr);

    fread(buf, sizeof(char), fileSize, fileToRead);
    *(buf + fileSize - 2) = '\n';
    *(buf + fileSize - 1)     = '\0';
}

size_t CountLines(const char* str, const size_t len) {
    assert(str != nullptr);

    const char* iter = str;
    size_t lines = 0;

    while (iter != str + len) {
        if (*iter == '\n')
            lines++;
        iter++;
    }

    return lines;
}

void SwapN(char* str,const size_t len) {
    assert(str != nullptr);

    char* iter = str;

    while (iter != str + len) {
        if (*iter == '\n')
            *iter = '\0';
        iter++;
    }
}

void FillText(char** text, char* buf, const size_t fileSize) {
    assert(text != nullptr);
    assert(buf  != nullptr);

    char** fillText = text;
    bool nLinePrev = true;

    char* iter = buf;

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
}

void PrintText(FILE* file, const size_t lines, const char* const* text) {
    assert(file != nullptr);
    assert(text != nullptr);

    for (size_t i = 0; i < lines; i++) {
        fprintf(file, "%s\n", *(text + i));
    }
}


