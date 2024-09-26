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

node *create_node(double valueDouble, char valueChar){
    node *temporario = NULL;
    do{
        temporario = (node*) malloc(1*sizeof(node));
    } while (temporario == NULL);
    temporario -> informacoes.valorDouble = valueDouble;
    temporario -> informacoes.valorChar = valueChar;
    temporario -> sucessor = NULL;
    temporario -> predecessor = NULL;
    return temporario;
}

/*
node *create_node_perso(){    
    node *temporario = NULL;
    do{
        temporario = (node*) malloc(1*sizeof(node));
    } while (temporario == NULL);
    fgets(temporario->informacoes.nome, 49, stdin);
    temporario->informacoes.nome[strlen(temporario->informacoes.nome) - 1] = '\0';
    temporario -> sucessor = NULL;
    temporario -> predecessor = NULL;
    return temporario;
}

node *create_full_node(){
    node *temporario = NULL;
    do{
        temporario = (node*) malloc(1*sizeof(node));
    } while (temporario == NULL);
    printf("Insira o nome\n>> ");
    fgets(temporario->informacoes.nome,50,stdin);
    temporario->informacoes.nome[strlen(temporario->informacoes.nome) - 1] = '\0';
    printf("Insira o valor:\n>> ");
    scanf("%d%*c", &temporario->informacoes.valor);
    return temporario;
}
*/

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
/*
node *minimun_c_list(c_linkedl *list){
    node *temporario = (list) -> inicio;
    node *menor = temporario;
    if((list) -> tamanho >= 1){
        for(int c = 1; c <= (list) -> tamanho; c++){
            if(menor -> informacoes.valor > temporario -> informacoes.valor){
                menor = temporario;
            }
            temporario = temporario -> sucessor;
        }
        return menor;
    }else{
        return NULL;
    }
}

node *maximun_c_list(c_linkedl *list){
    node *temporario = (list) -> inicio;
    node *maior = temporario;
    if((list) -> tamanho >= 1){
        for(int c = 1;c <= (list) -> tamanho; c++){
            if(maior -> informacoes.valor < temporario -> informacoes.valor){
                maior = temporario;
            }
            temporario = temporario -> sucessor;
        }
        return maior;
    } else{
        return NULL;
    }
}

node *search_key_c_list(c_linkedl *list, int key){
    node *temporario = (list) -> inicio;
    for(int c = 1;c <= (list) -> tamanho; c++){
        if(c == key){
            return temporario;
        }
        temporario = temporario -> sucessor;
    }
    return NULL;
}

node *search_value_c_list(c_linkedl *list, int value){
    node *temporario = (list) -> inicio;
    for(int c = 1;c <= (list) -> tamanho; c++){
        if(temporario -> informacoes.valor == value){
            return temporario;
        }
        temporario = temporario -> sucessor;
    }
    return NULL;
}

node *search_name_c_list(c_linkedl *list, char *string){
    node *temporario = list->inicio;
    for(int c = 1; c <= list->tamanho; c++){
        if(strcmp(temporario->informacoes.nome, string) == 0){
            return temporario;
        }
        temporario = temporario->sucessor;
    } 
    return NULL;
}
*/

void show_c_list(c_linkedl *list){
    if((list) -> tamanho >= 1){
        node *temporario = (list) -> inicio;
        printf("Elementos da lista:");
        for(int c = 0; c < (list) -> tamanho; c++){
            printf(" %lf | %c", temporario -> informacoes.valorDouble, temporario->informacoes.valorChar);
            temporario = temporario -> sucessor;
        }
        putchar('\n');
    }else{
        printf("Lista vazia!\n");
    }
}

/*

void insertion_sort(c_linkedl *list){
    if(list -> tamanho >= 1){
        c_linkedl lista_nova;
        lista_nova = create_c_list();
        int maximum_size = list -> tamanho;
        
        node *temporario = NULL;
        for(int c = 0; c < maximum_size; c++){
            temporario = minimun_c_list(list);
            del_c_list_element(list, temporario, 0);
            insert_c_list(&lista_nova, temporario);
        }
        *list = lista_nova;
    }
}

int opc_exc(c_linkedl *list){
    int opcao, valor, chave;
    node *temporario = NULL;
    printf("\n\nInsira o desejado:\n\n1: Inserir\n2: Deletar (por chave)\n3: Deletar (por valor)\n4: Procurar (por chave)\n5: Procurar (por valor)\n6: Mostrar maior valor\n7: Mostrar menor valor\n8: Ordenar\n9: Mostrar lista\n10: Sair\n\n");
    do{
        scanf("%d", &opcao);
    } while (opcao < 1 && opcao > 10);
    
    switch (opcao){
        case 1:
            printf("Insira o valor:\n>> ");
            scanf("%d", &valor);
            insert_c_list((list), create_node(valor));
            break;
        case 2:
            printf("Insira chave:\n>> ");
            scanf("%d", &chave);
            del_c_list_element((list), search_key_c_list((list), chave), 1);
            break;
        case 3:
            printf("Insira o valor:\n>> ");
            scanf("%d", &valor);
            del_c_list_element((list), search_value_c_list((list), valor), 1);
            break;
        case 4:
             printf("Insira o valor:\n>> ");
            scanf("%d", &chave);
            printf("Endereco: %p\n", search_key_c_list((list), chave));
            break;
        case 5:
            printf("Insira o valor:\n>> ");
            scanf("%d", &valor);
            printf("Endereco: %p\n", search_value_c_list((list), valor));
            break;
        case 6:
            temporario = maximun_c_list((list));
            if(temporario != NULL){
                printf("Endereco: %p | Valor: %d", temporario, temporario -> informacoes.valor);
            } else{
                printf("Nao foi possivel identificar maior valor.\n");
            }
            break;
        case 7:
            temporario = minimun_c_list((list));
            if(temporario != NULL){
                printf("Endereco: %p | Valor: %d", temporario, temporario -> informacoes.valor);
            } else{
                printf("Nao foi possivel identificar o menor valor.\n");
            }
            break;    
        case 8:
            insertion_sort(list);
            break;
        case 9:
            show_c_list((list));
            break;
        case 10:
            kill_c_list(list);
            return 0;
    }

    return 1;
}
*/
