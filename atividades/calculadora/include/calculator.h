#ifndef  _CALCULATOR_

#define _CALCULATOR_

#include "linked_list.h"
#include "dinamic_queue_and_stack.h"
#include <stdlib.h>
#include <string.h>

#define ll long long

typedef struct _calculadora{
    dstack *valores;
    dstack *operadores;
} calculadora;

typedef c_linkedl data;

calculadora* create_calculadora();

data* create_data();

void kill_data(data* x);

void kill_calculadora(calculadora *calc);

void read_data(data *dadosLidos, char* leitura);

void calcular(calculadora* calc);

double solve(data *dadosLidos);

#endif