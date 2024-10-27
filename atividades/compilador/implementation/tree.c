#include "./../header/tree.h"

No* cria_no(const char* valor) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memória para o nó");
        return NULL;
    }
    novo_no->valor = strdup(valor);  // Copia o valor da string
    novo_no->esquerda = novo_no->direita = NULL;
    return novo_no;
}


No* insere(No* raiz, const char* valor) {
    if (raiz == NULL) {
        return cria_no(valor);
    }

    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = insere(raiz->esquerda, valor);
    } else if (strcmp(valor, raiz->valor) > 0) {
        raiz->direita = insere(raiz->direita, valor);
    }
    return raiz;
}

void insereEncap(No** raiz, const char* valor){
    *raiz = insere(*raiz, valor);
}

int busca(No* raiz, const char* valor) {
    if (raiz == NULL) {
        return 0;  // Não encontrado
    }

    int cmp = strcmp(valor, raiz->valor);
    if (cmp == 0) {
        return 1;  // Encontrado
    } else if (cmp < 0) {
        return busca(raiz->esquerda, valor);
    } else {
        return busca(raiz->direita, valor);
    }
}

No* buscaEndereco(No* raiz, const char*valor){
    if(raiz == NULL){
        return NULL;
    }

    int cmp = strcmp(valor, raiz->valor);
    if(cmp == 0){
        return raiz;
    } else if(cmp < 0){
        return buscaEndereco(raiz->esquerda, valor);
    }else{
        return buscaEndereco(raiz->direita, valor);
    }

}

void em_ordem(No* raiz) {
    //printf("%p\n", raiz);
    if (raiz != NULL) {
        em_ordem(raiz->esquerda);
        printf("%s\n", raiz->valor);
        em_ordem(raiz->direita);
    }
}

No* remove_no(No* raiz, const char* valor) {
    if (raiz == NULL) {
        return NULL;
    }

    int cmp = strcmp(valor, raiz->valor);
    if (cmp < 0) {
        raiz->esquerda = remove_no(raiz->esquerda, valor);
    } else if (cmp > 0) {
        raiz->direita = remove_no(raiz->direita, valor);
    } else {
        // Nó encontrado
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz->valor);
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz->valor);
            free(raiz);
            return temp;
        }

        // Nó com dois filhos
        No* temp = raiz->direita;
        while (temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        free(raiz->valor);
        raiz->valor = strdup(temp->valor);
        raiz->direita = remove_no(raiz->direita, temp->valor);
    }
    return raiz;
}

void libera_arvore(No* raiz) {
    if (raiz != NULL) {
        libera_arvore(raiz->esquerda);
        libera_arvore(raiz->direita);
        free(raiz->valor);
        free(raiz);
    }
}

void createPrimitiveTree(primitiveTree** tree){


    *tree = (primitiveTree*) malloc(sizeof(primitiveTree));
    if(*tree == NULL){
        printf("Failed at createPrimitiveTree...\nAborting...");
        fflush(stdout);
        abort();
    }
}

void insertPrimitiveTree(primitiveTree* tree, int qtd, char** values){
    /*
    for(int c = 0; c < qtd; c++){
        printf("%s\n", values[c]);
    }
    */ 
    
    tree->tree = (pairTree*) malloc(qtd * sizeof(pairTree));
    tree->size = qtd;
    pairTree* shortName = tree->tree;
    for(int c = 0; c < qtd; c++){
        shortName[c].raiz = NULL;
        shortName[c].string = (char*) malloc(1 + strlen(values[c]));
        if(shortName[c].string == NULL){
            printf("Failed at malloc in insertPrimitiveTree...\nAborting...\n");
            fflush(stdout);
            abort();
        }
        strcpy(shortName[c].string, values[c]);
        //printf("%s\n", shortName[c].string);
    }
}

No** findPrimitiveType(primitiveTree* tree, char* value){
    if(tree == NULL || value == NULL){
        return NULL;
    }
    for(int c = 0; c < tree->size; c++){
        if(tree->tree[c].string == NULL){
            continue;
        }
        if(strcmp(value, tree->tree[c].string) == 0){
            return &(tree->tree[c].raiz);
        }
    }
    return NULL;
}

void deletePrimitiveTree(primitiveTree** tree){
    if(tree == NULL)
        return;
    if((*tree)->tree == NULL)
        return;

    long tree_size = (*tree)->size;
    pairTree* pair = (*tree)->tree;
    for(int c = 0; c < tree_size; c++){
        if(pair->string != NULL){
            free(pair->string);
        }
        if(pair->raiz != NULL){
            libera_arvore(pair->raiz);
        }
    }
}

void showPairs(primitiveTree** tree){
    if(tree == NULL)    
        return;
    if(*tree == NULL)
        return;
    
    long sizeTree = (*tree)->size;
    pairTree* shortName = (*tree)->tree;
    if(shortName == NULL){
        printf("Null tree at showpairs\n");
        return;
    }
    for(int c = 0; c < sizeTree; c++){
        printf("String: %p\n", shortName[c].string);
        printf("Root of tree: %p\n", shortName[c].raiz);
    }
}

void startPrimitiveTree(primitiveTree** tree){
    createPrimitiveTree(tree);
    //printf("%p\n", *tree);
    char* valores[]  = {"int", "long", "double", "float", "int*", "long*", "double*", "char", "char*", "long long", "long long*"};
    int size = 11;
    insertPrimitiveTree(*tree, size, valores);
    //showPairs(tree);
    //showPrimitiveTree(tree);
    
    //printf("%p\n", (*tree)->tree);
    //em_ordem((*tree)->tree->raiz);
}

void insertInPrimitiveType(primitiveTree** tree, char* typeOfTree, char* value){  
    
    if(tree == NULL){
        printf("NULL at inserInPrimitiveType");
    }
    No** correctTree = findPrimitiveType(*tree, typeOfTree);
    if(correctTree == NULL){
        printf("Tree not found at inserInPrimitiveType");
        return;
    }

    insereEncap(correctTree, value);
}

void showPrimitiveTree(primitiveTree** tree){
    if(tree == NULL){
        return;
    }

    if((*tree)->tree == NULL){
        printf("tree is empty in showPrimitiveTree\n");
        return;
    }

    for(int c = 0; c < (*tree)->size; c++){
        em_ordem((*tree)->tree[c].raiz);
    }
}