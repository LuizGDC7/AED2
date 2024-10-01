#include "planilha.h"

char* preprocesso(char *input, int qtdLinhas){
    if(input == NULL)
        return NULL;

    char validChar[] = {'(', ')', '/', '*', '+', '-'};
    int sizeValidChar = strlen(validChar);

    ll sizeInput = strlen(input);
    char* nova = malloc(5 * sizeInput * sizeof(char));
    char buffer[20];
    int start = 0;

    for(int c = 0; c < sizeInput; c++){

        if(input[c] >= 'A' && input[c] <= 'A' + qtdLinhas - 1){
            start = 1;
            sprintf(buffer, "%c", input[c]);
            //strcat(buffer, input[c]);
            continue;
        }

        if(start){
            if((input[c] >= '0' && input[c] <= '9') || input[c] == '.' || input[c] == ','){
                sprintf(buffer, "%s%c", buffer, input[c]);
                //strcat(buffer, input[c]);
            }else{
                start = 0;
                strcat(nova, strcat(buffer, "\n"));
                strcpy(buffer, "");
            }
        }


        if(!start){

            if(input[c] >= '0' && input[c] <= '9'){
                start = 1;
                strcpy(buffer, "");
                sprintf(buffer, "%s%c", buffer, input[c]);
            }

            for(int d = 0; d < sizeValidChar; d++){
                if(input[c] == validChar[d]){
                    sprintf(buffer, "%c\n", input[c]);
                    strcat(nova, buffer);  
                    break;      
                }
            }
            
        }

        if(start && c == sizeInput - 1){
            strcat(nova, buffer);
        }
    }

    return nova;

}

char* transcicao(double **matrix, int qtdLinhas, char* input){
    if(input == NULL)
        return NULL;

    ll sizeInput = strlen(input);
    char* nova = (char*) malloc(15 * sizeInput * sizeof(char));
    char buffer[15];
    int start = 0;
    char letra;
    int val;
    int pureNumber = 0;
    double dotPot = 0.1;

    for(int c = 0; c < sizeInput; c++){
        if(input[c] >= 'A' && input[c] <= 'A' + qtdLinhas){
            letra = input[c];
            start = 1;
            val = 0;
            continue;
        }

        if(start || pureNumber){
            if(input[c] >= '0' && input[c] <= '9'){
                val *= 10;
                val += input[c] - '0';
            }else{
                start = 0;
                strcpy(buffer, "");
                sprintf(buffer, "%g", matrix[letra - 'A'][val]);
                strcat(nova, buffer);
            }
        }

        if(start && c == sizeInput - 1){
            strcpy(buffer, "");
            sprintf(buffer, "%g", matrix[letra - 'A'][val]);
            strcat(nova, buffer);
        }

        if(!start){
            if(input[c] == '\n')
                continue;
            
            /*
            if(input[c] >= '0' && input[c] <= '*'){
                pureNumber = 1;
                val = 0;
                val += ;
            }
            */

            strcpy(buffer, "");
            sprintf(buffer, "%c", input[c]);
            strcat(nova, buffer);
        }
    }
}

char* leituraSuja(double **matrix, int qtdLinhas, int qtdColunas){

    for(int c = 0; c < qtdLinhas; c++){
        for(int d = 0; d < qtdColunas; d++){
            printf("Insira valor do item %c%d\n", 'A' + c, d);
            scanf(" %lf%*c", &matrix[c][d]);
        }
    }

    char* leitura = NULL;
    leitura = (char*) malloc(10000 * sizeof(char));
    printf("Insira sequencia de operacoes desejada:\n");
    scanf(" \n%[^\n]%*c", leitura);

    return leitura;
}