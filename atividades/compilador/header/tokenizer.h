#ifndef _TOKENIZER_

#define _TOKENIZER_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

/*

- Verificar blocos { } [ ] ( )  " "    ' ' => percorrer e por em pilha
- Sintaxe dos comandos ??? 
+ include => se encontrar, adicionar o resto da linha em uma string
+ main => separar
+ printf => separar
+ scanf => separar
+ if else => separar e colocar o resultado numa pilha
+ for ???
+ while => separar
+ switch case => FILHO DA PUTA
- Expressões ????
*/

/*

Algumas regras para garantir que eu consiga fazer meu programa funcionar:

A declaração das funções precisa ser completa:

tipo nome(argumento){ coisas }

if(){}
else{}
while(){}

vou separar em duas partes: declaração por meio de tipo e uso. Agora vou precisar dos dicionários

Não vou verificar o tipo das variáveis, mas preciso verificar se a quantidade está ok dentro das funções

*/

/*

Vou ter meus tipos primitivos e suas árvores, vou usar elas para inserção e para verificar existência.


tipos -> ("tipo", endereço da árvore do tipo)

Função -> armazenar nome das variáveis, e quais são as variáveis internas. Serão armazenadas na declaração


*/