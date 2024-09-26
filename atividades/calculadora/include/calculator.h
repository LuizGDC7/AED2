#ifndef  _CALCULATOR_

#define _CALCULATOR_

#include "linked_list.h"
#include "dinamic_queue_and_stack.h"

#define ll long long

typedef struct _calculadora{
    dstack valores;
    dstack operadores;
} calculadora;

typedef struct _data{
    c_linkedl vals;
    c_linkedl* adress;
} data;

void create_calculadora(calculadora* calc);

void create_data(data *dados);

void read_data(data *dados, char* leitura);

#endif