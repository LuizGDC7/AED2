#include "calculator.h"
#include "string.h"

#define ll long long

void create_calculadora(calculadora* calc){
    create_stack(&(calc->operadores));
    create_stack(&(calc->valores));
}

void create_data(data *dados){
    create_c_list(dados->vals);
    dados->adress = &(dados->vals);
}

void read_data(data *dados, char* leitura){
    ll sizeLeitura = strlen(leitura);
    for(int c = 0; c < sizeLeitura; c++){
        if(
            (leitura[c] >= '0' && leitura[c] <= '9') ||
            leitura[c] == '+' ||
            leitura[c] == '-' ||
            leitura[c] == '*' ||
            leitura[c] == '/' ||
            leitura[c] == '(' ||
            leitura[c] == ')' ||
            leitura[c] == ' '
        ){
            insert_c_list(dados->adress, create_node(-1, leitura[c]));
        }else{
            abort();
        }
    }
}

