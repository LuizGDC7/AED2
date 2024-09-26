#include "calculator.h"
#include <stdio.h>

int main(){
    data valores;
    create_data(&valores);
    char* leitura = NULL;
    scanf("%m[^\n]", &leitura);
    
    read_data(&valores, leitura);


    show_c_list(valores.adress);

    free(leitura);

    return 0;
}