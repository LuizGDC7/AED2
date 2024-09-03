#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

c_linkedl create_c_list(){
    c_linkedl temporario;
    temporario.tamanho = 0;
    temporario.inicio = NULL;
    temporario.fim = NULL; 
    return temporario;
}

void kill_c_list(c_linkedl *list){
    int maximo = (list)->tamanho;
    node *temporario = (list) -> inicio;
    if(maximo > 1){
        node *temporario2 = NULL;
        for(int c = 0; c < maximo; c++){
            temporario2 = temporario -> sucessor;
            free(temporario);
            temporario = temporario2;
        }
        (list) -> inicio = NULL;
        (list) -> fim = NULL;
    } else if(maximo == 1){
        free((list) -> inicio);
        (list) -> fim = NULL;
        (list) -> inicio = NULL;
    }
    (list) -> tamanho = 0; 
}

node *create_node(int value){
    node *temporario = NULL;
    do{
        temporario = (node*) malloc(1*sizeof(node));
    } while (temporario == NULL);
    temporario -> informacoes.valor = value;
    temporario -> sucessor = NULL;
    temporario -> predecessor = NULL;
    return temporario;
}

void insert_c_list(c_linkedl *list, node *endereco){ //insercao pela cauda
    if( (list) -> tamanho >= 1){
        ((list) -> fim) -> sucessor = endereco;
        endereco -> predecessor = list -> fim;
        (list) -> fim = endereco;
        (list) -> tamanho++;
    } else{
        (list) -> fim = endereco;
        (list) -> inicio = endereco;
        (list) -> tamanho++;
    }
}

void del_c_list_element(c_linkedl *list, node *endereco, int dar_free){
    if(endereco != NULL){
        if(endereco == list -> inicio){
            list -> inicio = (endereco) -> sucessor;
            if(dar_free == 1){
                free(endereco);
            }
        } else if(endereco == list ->fim){
            list -> fim = (list -> fim)->predecessor;
            if(dar_free == 1){
                free(endereco);
            }
        }else{
            ((endereco) -> predecessor) -> sucessor = (endereco) -> sucessor;
            (endereco -> sucessor) -> predecessor = (endereco) -> predecessor;
            if(dar_free == 1){
                free(endereco);
            }
        }
        list -> tamanho--;
        if((list) -> tamanho == 0){
            (list) -> inicio = NULL;
            (list) -> fim = NULL;
        }
    }
}

void show_c_list(c_linkedl *list){
    if((list) -> tamanho >= 1){
        node *temporario = (list) -> inicio;
        printf("Elementos da lista:");
        for(int c = 0; c < (list) -> tamanho; c++){
            printf(" %d", temporario -> informacoes.valor);
            temporario = temporario -> sucessor;
        }
        putchar('\n');
    }else{
        printf("Lista vazia!\n");
    }
}