#include "calculator.h"
#include "string.h"

#define ll long long

void create_calculadora(calculadora* calc){
    create_stack(&(calc->operadores));
    create_stack(&(calc->valores));
}

void create_data(data *dados){
    dados->adress = &(dados->vals);
    create_c_list(dados->adress);
}

void read_data(data *dados, char* leitura){
    ll sizeLeitura = strlen(leitura);
    int isNumber = 0;
    int dot = 0;
    double val = 0;
    double dotPot = 0.1;
    //double pot = 1;
    for(int c = 0; c < sizeLeitura; c++){
        if(leitura[c] >= '0' && leitura[c] <= '9'){
            isNumber = 1;
            if(dot){
                val += (leitura[c] - '0') * dotPot;
                dotPot /= 10;
            }else{
                val *= 10;
                val += leitura[c] - '0';
            }
            
        }else if(
            leitura[c] == '+' ||
            leitura[c] == '-' ||
            leitura[c] == '*' ||
            leitura[c] == '/' ||
            leitura[c] == '(' ||
            leitura[c] == ')' ||
            leitura[c] == ' '
        ){
            if(isNumber){
                insert_c_list(dados->adress, create_node(val, '\0'));
                val = 0;
                isNumber = 0;
                dot = 0;
                dotPot = 0.1;
            }
            insert_c_list(dados->adress, create_node(0, leitura[c]));
        }else if(leitura[c] == '.'){
            dot = 1;
        }

        if(isNumber && c == sizeLeitura - 1){
            insert_c_list(dados->adress, create_node(val, '\0'));            
        }

            //
        /*else{
            abort();
        }*/
    }
}

double calcular(data *dados){
    calculadora calc;
    create_calculadora(&calc);
    while(dados->vals.tamanho){
        if(dados->vals.inicio.){

        }
    }
}