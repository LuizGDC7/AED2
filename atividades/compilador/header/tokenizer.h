#ifndef _TOKENIZER_

#define _TOKENIZER_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct rowInfo{
    long size;
    char *value;
} rowInfo;

typedef struct matrixInfo{
    long rows;
    char **value;
} matrixInfo;

void freeRowInfo(rowInfo* info);

void freeMatrix(matrixInfo* info);

rowInfo *open(const char* namefile);

matrixInfo* tokenizer(rowInfo *input);

#endif

