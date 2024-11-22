#include "./header/tokenizer.h"
#include "./header/tree.h"

int main(int argc, char *argv[]){


    if(argc != 2){
        printf("Invalid format...\nAborting...");
        abort();
    }
    rowInfo* input = open(argv[1]);
    matrixInfo *tokens = tokenizer(input);
    
    primitiveTree* raiz = NULL;
    startPrimitiveTree(&raiz);
    preprocess(&raiz, input);
    deletePrimitiveTree(&raiz);
    free(input);
    //free(tokens);

    return 0;
}