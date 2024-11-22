#ifndef _TREE_

#define _TREE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "./../header/tokenizer.h"

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

void insertInPrimitiveType(primitiveTree** tree, char* typeOfTree, char* value); // Insere variáveis e funções em seus respectivos tipos primitivos

void showPrimitiveTree(primitiveTree** tree); // Mostra 

void insertFunctionInPrimitiveType(primitiveTree** tree, char* typeOfTree, char* name, char* arguments, char* body);

No* insere2(No* raiz, const char* nome, char* arguments, char* body);

No* cria_no2(const char* valor, char* arguments, char* body);

void insereEncap2(No** raiz, const char* name, char* arguments, char* body);

int verificar_formatacao_funcao(const char *declaracao);

int verificar_declaracao_main(const char *declaracao);

int declaration(primitiveTree** primitive, char* primitiveType, rowInfo* info, int start);

void warningAndAbortion(char* warn);

int verificar_sintaxe_printf(const char *declaracao);

int verificar_sintaxe_scanf(const char *declaracao);

int verificar_sintaxe_if_else(const char *declaracao);

int verificar_sintaxe_while(const char *declaracao);

int verificar_sintaxe_for(const char *declaracao);

void preprocess(primitiveTree** primitive, rowInfo* info);

#endif

/*

08/09/1951

*/