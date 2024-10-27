#ifndef _TREE_

#define _TREE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore
typedef struct func{
    int numberOfArguments;
    char* body;
    char* arguments;
} func;

typedef struct No {
    char* valor;
    int isFunction;
    func functionStorage;
    struct No* esquerda;
    struct No* direita;
} No;


typedef struct pairTree{
    char* string;
    No* raiz;
} pairTree;

typedef struct primitiveTree{
    int size;
    pairTree* tree;
} primitiveTree;

No* cria_no(const char* valor); // Cria um nó na árvore

No* insere(No* raiz, const char* valor); // cria um nó na árvore e retorna a raiz

void insereEncap(No** raiz, const char* valor); // encapsula o Insere

int busca(No* raiz, const char* valor); // verifica se um nó existe na árvore

No* buscaEndereco(No* raiz, const char*valor); // Busca o nó e retorna o endereço

void em_ordem(No* raiz); // Printa a árvore em ordem

No* remove_no(No* raiz, const char* valor); // deleta nó da árvore

void libera_arvore(No* raiz); // dá free na árvore inteira

void createPrimitiveTree(primitiveTree** tree); // Cria um vetor de pares primitivos

void insertPrimitiveTree(primitiveTree* tree, int qtd, char** values); // Insere valores no vetor de pares primitivos

No** findPrimitiveType(primitiveTree* tree, char* value); // Procura por um tipo primitivo e retorna um endereço

void deletePrimitiveTree(primitiveTree** tree); // deleta completamente a primitietree

void showPairs(primitiveTree** tree); // mostra string - nó na tree

void startPrimitiveTree(primitiveTree** tree); // inicia a primitiveTree

void insertInPrimitiveType(primitiveTree** tree, char* typeOfTree, char* value);

void showPrimitiveTree(primitiveTree** tree);


#endif