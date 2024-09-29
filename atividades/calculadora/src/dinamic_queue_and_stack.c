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