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

static void SwapChar(char* str,const size_t len, char start, char end);

static void FillText(Str* text, char* buf, const size_t fileSize);

// --------------------------------------

void GetData(Data* data, FILE* file) {
    assert(data != nullptr);
    assert(file != nullptr);

    data->bufSize = (size_t)FileSize(file) + 2;

    data->buf = (char*)calloc(data->bufSize, sizeof(char));

    FileRead(data->buf, data->bufSize, file);

    data->nLines = CountLines(data->buf, data->bufSize);

    SwapChar(data->buf, data->bufSize, '\n', '\0');

    data->text = (Str*)calloc(data->nLines+1, sizeof(Str));

    FillText(data->text, data->buf, data->bufSize);
}

void PutData(Data* data, FILE* file) {
    assert(data != nullptr);
    assert(file != nullptr);

    for (size_t i = 0; i < data->nLines; i++) {
        fprintf(file, "%s\n", (data->text + i)->str);
    }
}

void PutBuf(Data* data, FILE* file) {
    assert(data != nullptr);
    assert(file != nullptr);

    size_t iter = 0;
    while (iter < data->bufSize) {
        if (data->buf[iter] == '\0') {
            fputc('\n', file);
        } else {
            fputc(data->buf[iter], file);
        }
        iter++;
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

static void SwapChar(char* str,const size_t len, char start, char end) { //
    assert(str != nullptr);

    char* iter = str;

    while (iter != str + len) {
        if (*iter == start)
            *iter = end;
        iter++;
    }
}

static void FillText(Str* text, char* buf, const size_t fileSize) {
    assert(text != nullptr);
    assert(buf  != nullptr);

    Str* fillText = text;
    bool nLinePrev = true;

    char* iter = buf + strlen(buf) - 1;
    char* hold = buf;

    while (iter != buf + fileSize) {
        if (nLinePrev) {
            fillText->str = hold;
            fillText->len = iter - hold - 2;
            hold = iter;
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
