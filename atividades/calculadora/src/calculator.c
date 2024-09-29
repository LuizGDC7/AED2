#include "calculator.h"
#include "string.h"

#define ll long long

calculadora* create_calculadora(){

    calculadora* nova = NULL;
    nova = (calculadora*) malloc(sizeof(calculadora));
    nova->operadores = nova->valores = NULL;
    nova->operadores = (dstack*) malloc(sizeof(dstack));
    nova->valores = (dstack*) malloc(sizeof(dstack));
    create_stack(nova->operadores);
    create_stack(nova->valores);
    return nova;
}

data* create_data(){
    data *nova = NULL;
    nova = (data*) malloc(1*sizeof(data));
    nova = (c_linkedl*) malloc(sizeof(c_linkedl));
    nova->fim = NULL;
    nova->inicio = NULL;
    nova->tamanho = 0;
    return nova;
}

void kill_data(data* x){
    kill_c_list(x);
}

void kill_calculadora(calculadora *calc){
    kill_stack(calc->operadores);
    kill_stack(calc->valores);
}

void read_data(data *dadosLidos, char* leitura){
    ll sizeLeitura = strlen(leitura);
    int isNumber = 0;
    int dot = 0;
    double val = 0;
    double dotPot = 0.1;
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
            leitura[c] == ')'
        ){
            if(isNumber){
                insert_c_list(dadosLidos, create_node(val, '\0'));
                val = 0;
                isNumber = 0;
                dot = 0;
                dotPot = 0.1;
            }
            insert_c_list(dadosLidos, create_node(0, leitura[c]));
        }else if(leitura[c] == '.' || leitura[c] == ','){
            dot = 1;
        }

        if(isNumber && c == sizeLeitura - 1){
            insert_c_list(dadosLidos, create_node(val, '\0'));            
        }
    }
}

void oposite(calculadora *calc){
    if(calc->operadores->pilha.tamanho < 1){
        printf("LACK OF OPERATORS");
        abort();
    }
    
     if(calc->valores->pilha.tamanho < 1){
        printf("LACK OF NUMBERS");
        abort();
    }

    double val = (-1) * calc->valores->pilha.fim->informacoes->valorDouble;
    calc->valores->pilha.fim->informacoes->valorDouble = val;
    calc->operadores->pilha.fim->informacoes->valorChar = '+';
}

void calcular(calculadora* calc){

    if(calc->operadores->pilha.tamanho < 1){
        printf("LACK OF OPERATORS");
        abort();
    }
    
     if(calc->valores->pilha.tamanho < 2){
        printf("LACK OF NUMBERS");
        abort();
    }

    double val1, val2, res = 0;
    char operacao = calc->operadores->pilha.fim->informacoes->valorChar;
    val2 = calc->valores->pilha.fim->informacoes->valorDouble;
    val1 = calc->valores->pilha.fim->predecessor->informacoes->valorDouble;
    pop_stack(calc->valores);
    pop_stack(calc->valores);
    pop_stack(calc->operadores);

    switch(operacao){
        case '+':
            res = val1 + val2;
            break;
        case '-':
            res = val1 - val2;
            break;
        case '*':
            res = val1 * val2;
            break;
        case '/': 
            res = val1 / val2;
            break;
        default:
            abort();
    }

    //printf("\n%.3lf %c %.3lf = %.3lf\n", val1, operacao, val2, res);
    insert_stack(calc->valores, create_node(res, '\0'));
    //show_c_list(&(calc->valores->pilha));
    //show_c_list(&(calc->operadores->pilha));
}

double solve(data *dadosLidos){
    calculadora *calc = create_calculadora();
    int breakLoop = 0;
    //int doCalc = 0;
    int lastIsNumber = 0;
    double returnValue = 0;

    while((dadosLidos)->tamanho && !breakLoop){
        char input = dadosLidos->inicio->informacoes->valorChar;
        double val = dadosLidos->inicio->informacoes->valorDouble;
        char lastOp = calc->operadores->pilha.fim == NULL ? '\0' : calc->operadores->pilha.fim->informacoes->valorChar;
        del_c_list_element(dadosLidos, dadosLidos->inicio, 1);
        
        //printf("Last Operator:%c | lastIsNumber: %d\n", lastOp, lastIsNumber);

        if(lastOp == '-' && lastIsNumber){
            oposite(calc);
        }

        if((lastOp == '*' || lastOp == '/') && lastIsNumber){
            calcular(calc);
            //doCalc = 0;
        }

        switch (input){
        case '\0':
            insert_stack(calc->valores, create_node(val, '\0'));
            lastIsNumber = 1;
            break;
        case '(':
            insert_stack(calc->valores, create_node(solve(dadosLidos), '\0'));
            lastIsNumber = 1;
            break;
        case ')':
            breakLoop = 1;
            break;
        /*
        case '*':
        case '/':
            doCalc = 1;
        */
        default:
            lastIsNumber = 0;
            insert_stack(calc->operadores, create_node(0, input));
            break;
        }
    }

    for(; calc->valores->pilha.tamanho > 1; ){
        calcular(calc);
    }

    returnValue = calc->valores->pilha.inicio->informacoes->valorDouble;
    kill_calculadora(calc);
    return returnValue;    
}


