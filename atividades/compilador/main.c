#include "./header/tokenizer.h"
#include "./header/tree.h"

int main(/*int argc, char *argv[]*/){

/*
    if(argc != 2){
        printf("Invalid format...\nAborting...");
        abort();
    }
    rowInfo* input = open(argv[1]);
    matrixInfo *tokens = tokenizer(input);

    for(int c = 0; c < tokens->rows; c++){
        printf("%s\n", tokens->value[c]);
    }

    
    free(input);
    free(tokens);
*/
    primitiveTree* raiz = NULL;
    startPrimitiveTree(&raiz);
    //showPairs(&raiz);
    insertInPrimitiveType(&raiz, "int", "teste1");
    
    insertInPrimitiveType(&raiz, "int", "teste2");
    insertInPrimitiveType(&raiz, "double", "teste3");
    
    showPrimitiveTree(&raiz);
    

    //deletePrimitiveTree(&raiz);

    return 0;
}