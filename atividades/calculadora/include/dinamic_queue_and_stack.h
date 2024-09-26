#ifndef DINAMIC_QUEUE_AND_STACK

#define DINAMIC_QUEUE_AND_STACK

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _dstack{
    c_linkedl pilha;
} dstack;

typedef struct _dqueue{
    c_linkedl queue;
    //node sentinela;
} dqueue;

void create_stack(dstack *endereco);

void kill_stack(dstack *stack);

void insert_stack(dstack *stack, node *endereco);

void pop_stack(dstack *stack);

node *peek_stack(dstack *stack);

void create_queue(dqueue *endereco);

void kill_queue(dqueue *queue);

void enqueue(dqueue *queue, node *endereco);

void unqueue(dqueue *queue);

node *peek_queue(dqueue *queue);

int menu_queue(dqueue *queue);

int menu_stack(dstack *stack);

#endif