#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// struct Data {
//     char* buf;
//     char** text;
//     size_t fileSize;
//     size_t nLines;
// };

ssize_t FileSize(FILE* file);

size_t CountLines(const char* str, const size_t len);

void SwapN(char* str,const  size_t len);

void FillText(char** text, char* buf, const size_t fileSize);

void PrintText(FILE* file, const size_t lines, const char* const* text);

void FileRead(char* buf, size_t fileSize, FILE* fileToRead);

#endif
