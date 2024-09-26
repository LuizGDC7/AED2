#include "dinamic_queue_and_stack.h"
#include "linked_list.h"

void create_stack(dstack *endereco){
    endereco->pilha.tamanho = 0;
    endereco->pilha.inicio = NULL;
    endereco->pilha.fim = NULL;
}

void kill_stack(dstack *stack){
    kill_c_list(&(stack->pilha));
}

void insert_stack(dstack *stack, node *endereco){
    insert_c_list(&(stack->pilha), endereco);
}

void pop_stack(dstack *stack){
    del_c_list_element(&(stack->pilha), stack->pilha.fim, 1);
}

node *peek_stack(dstack *stack){
    if(stack->pilha.tamanho > 0){
        return stack->pilha.fim;
    }else{
        return NULL;
    }
}

void create_queue(dqueue *endereco){
    //endereco->sentinela.predecessor = endereco->queue.fim;
    //endereco->sentinela.sucessor = endereco->queue.inicio;
    endereco->queue.tamanho = 0;
    endereco->queue.inicio = NULL;
    endereco->queue.fim = NULL;
}

void kill_queue(dqueue *queue){
    kill_c_list(&(queue->queue));
}

void enqueue(dqueue *queue, node *endereco){
    insert_c_list(&(queue->queue), endereco);
}

void unqueue(dqueue *queue){
    del_c_list_element(&(queue->queue), queue->queue.inicio, 1);
}

node *peek_queue(dqueue *queue){
    if(queue->queue.tamanho > 0){
        return queue->queue.inicio;
    }else{
        return NULL;
    }
}
/*

int menu_queue(dqueue *queue){
    int opcao, valor;
    node *temporario = NULL;
    printf("\n\nInsira o desejado:\n\n1: Inserir\n2: Deletar\n3: Peek\n4: Sair\n\n");
    do{
        scanf("%d", &opcao);
    } while (opcao < 1 && opcao > 4);
    
    switch (opcao){
        case 1:
            printf("Insira o valor:\n>> ");
            scanf("%d", &valor);
            enqueue(queue,  create_node(valor));
            break;
        case 2:
            unqueue(queue);
            break;
        case 3:
            temporario = peek_queue(queue);
            if(temporario != NULL){
                printf("Endereco: %p | Valor: %d\n", temporario, temporario->informacoes.valor);
            }else{
                printf("Endereco: %p | Valor: %p", temporario, temporario);
            }
            
            break;
        case 4:
            kill_queue(queue);
            return 0;
    }

    return 1;
}

int menu_stack(dstack *stack){
    int opcao, valor;
    node *temporario = NULL;
    printf("\n\nInsira o desejado:\n\n1: Inserir\n2: Deletar\n3: Peek\n4: Sair\n\n");
    do{
        scanf("%d", &opcao);
    } while (opcao < 1 && opcao > 4);
    
    switch (opcao){
        case 1:
            printf("Insira o valor:\n>> ");
            scanf("%d", &valor);
            insert_stack(stack,  create_node(valor));
            break;
        case 2:
            pop_stack(stack);
            break;
        case 3:
            temporario = peek_stack(stack);
            if(temporario != NULL){
                printf("Endereco: %p | Valor: %d\n", temporario, temporario->informacoes.valor);
            }else{
                printf("Endereco: %p | Valor: %p", temporario, temporario);
            }
            break;
        case 4:
            kill_stack(stack);
            return 0;
    }

    return 1;
}
*/