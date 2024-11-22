// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>
#include "./huffman.h"


int main(int argc, char* argv[]){

    if(argc != 2){
        riseWarning("Incorrect use of program");
    }

    //printf("%s\n%s\n%d\n", argv[0], argv[1], argc);

    int size; 
    char* inp = readFile(argv[1], &size);
    //printf("%d\n", size);
    input* wrap = wrapData(inp, size);
    //printf("Finalizei\n");
    //printf("%s\n%s\n%d\n%d\n", wrap->stringInput, wrap->stringComposition, wrap->stringSize, wrap->characterCompositionQtd);
/*
    printf("%s\n%s\n%d\n%d\n", wrap->stringInput, wrap->stringComposition, wrap->stringSize, wrap->characterCompositionQtd);


    for(int c = 0; c < wrap->characterCompositionQtd; c++){
        printf("%d ", wrap->frequency[c]);
    }
*/


    //printf("\n");



    HuffmanCodes(wrap->stringComposition, wrap->frequency, wrap->characterCompositionQtd);
    destroyInput(wrap);

    return 0;
}
