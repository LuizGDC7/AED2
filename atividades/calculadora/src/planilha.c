#include "planilha.h"

char* preprocess(char *input, int maxRows){
    if(input == NULL)
        return NULL;

    ll sizeInput = strlen(input);
    char* nova = malloc(5 * sizeInput * sizeof(char));
    char buffer[20];
    int start = 0;
    for(int c = 0; c < sizeInput; c++){

        if(input[c] >= 'A' && input[c] <= 'A' + maxRows - 1){
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

        if(start && c == sizeInput - 1){
            strcat(nova, buffer);
        }

        if(!start){
            sprintf(buffer, "%c\n", input[c]);
            strcat(nova, buffer);
        }
    }

    return nova;

}

ll coluna(char* val){
    int tamanho = strlen(val);
    ll res = 0;
    for(int c = 1; c < tamanho; c++){
        res *= 10;
        res += val[c] - '0';
    }

    return res;
}

/*
char* transcicao(double **matrice, int maxRows, char* input){
    if(input == NULL)
        return NULL;
    ll sizeInput = strlen(input);
    char* nova = (char*) malloc(15 * sizeInput * sizeof(char));
    int consumo = 0;
    char twoChars[2];
    char buffer[15];

    for(int c = 0; c < sizeInput; c++){
        twoChars[consumo] = input[c];
        consumo++;

        if(consumo == 1 && c < sizeInput - 1)
            continue;
        
        if(c == sizeInput - 1){
            if(consumo == 1)
                strcat(nova, twoChars[0]);
            else if(consumo == 2){
                if((twoChars[0] >= 'A' && twoChars[0] <= ('A' + maxRows)) &&  )
            }
        }





    }
}

*/