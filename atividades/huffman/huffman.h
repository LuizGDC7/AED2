#ifndef _HUFFMAN_

#define _HUFFMAN_

#include "./heap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct input{
    char* stringInput;
    char* stringComposition;
    int stringSize;
    int characterCompositionQtd;
    int* frequency;
} input;

char* readFile(const char* nome_arquivo, int* size);

void destroyInput(input* in);

void riseWarning(char* warning);

int* countCharacters(char* stringInput, int size);

input* wrapData(char* stringInput, int size);

MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);

void printCodes(MinHeapNode* root, int arr[], int top);

void HuffmanCodes(char data[], int freq[], int size);


#endif

