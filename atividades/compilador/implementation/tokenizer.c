#include "./../header/tokenizer.h"

void freeRowInfo(rowInfo* info){
    if(info == NULL)
        return;
    if(info->value != NULL)
        free(info->value);
    free(info);
}

void freeMatrix(matrixInfo* info){
    if(info == NULL)
        return;
    if(info->value != NULL){
        for(int c = 0; c < info->rows; c++){
            if(info->value[c] != NULL)
                free(info->value[c]);
        }
    }
    free(info);
}

rowInfo *open(const char* namefile){
    FILE *file = fopen(namefile, "r");  // Abra o arquivo em modo leitura
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    // Ir até o final do arquivo para determinar o tamanho
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);  // Volta para o início do arquivo

    // Aloca memória para armazenar o conteúdo do arquivo
    char *buffer = malloc(file_size + 1);  // +1 para o caractere nulo
    if (buffer == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    // Lê o arquivo inteiro para o buffer
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';  // Adiciona o caractere nulo no final para uma string

    //printf("Conteúdo do arquivo:\n%s\n", buffer);

    // Limpeza
    fclose(file);  // Fecha o arquivo

    rowInfo *retorno = (rowInfo *) malloc(sizeof(rowInfo));
    retorno->size = file_size + 1;
    retorno->value = buffer;

    return retorno;
}

matrixInfo* tokenizer(rowInfo *input){


    if(input == NULL){
        printf("Failed at tokenizer... \nAborting...\n");
        fflush(stdout);
        abort();
    }

    if(input->value == NULL){
        printf("Failed at tokenizer...\nAborting...\n");
        fflush(stdout);
        abort();
    }

    char* info = input->value;

    const char delimiters[] = "\n";
    int i = 0, MAX_TOKENS = 10000;
    char* token = strtok(info, delimiters);
    char** tokens = (char**) malloc(MAX_TOKENS * sizeof(char*));

    while(token != NULL && i < MAX_TOKENS){
        int lenght = strlen(token) + 1;
        tokens[i] = (char*) malloc(lenght * sizeof(char));
        if(tokens[i] == NULL){
            printf("Malloc failed at tokenizer...\nAborting\n");
            fflush(stdout);
            abort();
        }
        strcpy(tokens[i], token);
        i++;
        token = strtok(NULL, delimiters);
    }

    matrixInfo *retorno = (matrixInfo *) malloc(sizeof(matrixInfo));

    if(retorno == NULL){
        printf("Failed at malloc in Matrixinfo...\nAborting...");
        fflush(stdout);
        abort();
    }

    retorno->rows = i;
    retorno->value = tokens;

    return retorno;
}
/*
char **tokenizer2(char **processed){
    char **matrix = malloc
}
*/