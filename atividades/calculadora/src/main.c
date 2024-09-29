#include "calculator.h"
#include "planilha.h"
#include <stdio.h>

int main(){
    //data *valores = create_data();
    //calculadora* calc = create_calculadora();
    char leitura[10000];
    scanf(" %s[^\n]", leitura);

    char* preprocessado = preprocess(leitura, 26);

    //printf("%s", preprocessado);
    char * mundoDividido = strtok(preprocessado, "\n");;

    while(mundoDividido != NULL){
        int tamanho = strlen(mundoDividido);
        printf("Linha: %s ----- Tamanho: %lld\n", mundoDividido, tamanho);
        if(tamanho > 1) 
            //printf("%s possui valor %d", coluna(mundoDividido));


        mundoDividido = strtok(NULL, "\n");
    }
    
    /*
    read_data(valores, leitura);

    show_c_list(valores);

    printf("\n VALUE IS: %.3lf\n", solve(valores));

    kill_data(valores);
    kill_calculadora(calc);
    */
    
    //free(leitura);

    return 0;
}