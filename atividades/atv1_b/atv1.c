#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    double nota, frequencia;
    struct node *next;
} node;

typedef struct listaEncadeada {
    node *head;
} list;

void validarAprovacao(node *Aluno){
    char resultado[100] = "Aprovado";
    if(Aluno->nota < 6 || Aluno->frequencia < 75)
        strcpy(resultado,  "Reprovado por: ");
    if(Aluno->nota < 6)
        strcat(resultado, "nota ");
    if(Aluno->frequencia < 75)
        strcat(resultado, "frequencia");

    printf("%s\n", resultado);
}

int main(){
    list lista;
    lista.head = NULL;
    node *novo = NULL;
    for(int c = 0; c < 30; c++){
        if(c){
            novo->next = (node*) malloc(sizeof(node));
            novo = novo->next;
        }
        else{
            lista.head = (node*) malloc(sizeof(node));
            novo = lista.head;
        }
        novo->next = NULL;
        printf("Insira a nota do aluno %d: ", c + 1);
        scanf("%lf", &(novo->nota));
        printf("Insira a frequencia do aluno %d: ", c + 1);
        scanf("%lf", &(novo->frequencia));
    }
    novo = lista.head;
    for(int c = 0; novo != NULL; novo = novo->next, c++){
        printf("Aluno: %d\n", c);
        validarAprovacao(novo);
        printf("\n");
    }

    for(node *anterior = lista.head;anterior != NULL; anterior = novo){
        novo = anterior->next;
        free(anterior);
    }

    return 0;
}