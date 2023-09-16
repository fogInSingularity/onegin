#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

/// @brief holds string
struct Str {
    char* str;   ///< string intself
    ssize_t len; ///< len of string
};


/// @brief struct that holds file contents
struct Data {
    char* buf;      ///< buffer that holds file string
    size_t bufSize; ///< size of buffer in bytes

    Str* text;       ///< string array
    size_t nLines;  ///< number of strings
};


/**
 * @brief get data from file
 *
 * @param data Data struct
 * @param file file to get data from
*/
void GetData(Data* data, FILE* file);


/**
 * @brief put data to file
 *
 * @param data Data struct
 * @param file file to put data to
*/
void PutData(Data* data, FILE* file);


/**
 * @brief put buffer to file
 *
 * @param data Data struct
 * @param file file to put buffer to
*/
void PutBuf(Data* data, FILE* file);


/**
 * @brief free all data members
 *
 * @param data Data struct
*/
void FreeData(Data* data);

#endif
