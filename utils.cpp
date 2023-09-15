#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "utils.h"

// ---------------------------------------

static ssize_t FileSize(FILE* file);

static void FileRead(char* buf, size_t fileSize, FILE* fileToRead);

static size_t CountLines(const char* str, const size_t len);

static void SwapN(char* str,const  size_t len);

static void FillText(char** text, char* buf, const size_t fileSize);

// --------------------------------------

void GetData(Data* data, FILE* file) {
    assert(data != nullptr);
    assert(file != nullptr);

    data->bufSize = (size_t)FileSize(file) + 2;

    data->buf = (char*)calloc(data->bufSize, sizeof(char));

    FileRead(data->buf, data->bufSize, file);

    data->nLines = CountLines(data->buf, data->bufSize);

    SwapN(data->buf, data->bufSize);

    data->text = (char**)calloc(data->nLines+1, sizeof(char*));

    FillText(data->text, data->buf, data->bufSize);
}

void PutData(Data* data, FILE* file) {
    assert(data != nullptr);
    assert(file != nullptr);

    for (size_t i = 0; i < data->nLines; i++) {
        fprintf(file, "%s\n", *(data->text + i));
    }
}

void FreeData(Data* data) {
    free(data->buf);
    data->buf = nullptr;

    free(data->text);
    data->text = nullptr;
}

// -------------------------------------

static ssize_t FileSize(FILE* file) { //
    assert(file != nullptr);

    fseek(file, 0, SEEK_END);

    ssize_t size = ftell(file);

    fseek(file, 0, SEEK_SET);

    return size;
}

static void FileRead(char* buf, size_t fileSize, FILE* fileToRead) { //
    assert(buf        != nullptr);
    assert(fileToRead != nullptr);

    fread(buf, sizeof(char), fileSize, fileToRead);
    *(buf + fileSize - 2) = '\n';
    *(buf + fileSize - 1)     = '\0';
}

static size_t CountLines(const char* str, const size_t len) { //
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

static void SwapN(char* str,const size_t len) { //
    assert(str != nullptr);

    char* iter = str;

    while (iter != str + len) {
        if (*iter == '\n')
            *iter = '\0';
        iter++;
    }
}

static void FillText(char** text, char* buf, const size_t fileSize) { //
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
