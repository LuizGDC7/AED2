#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    double nota;
    double frequencia;
} aluno;

void validarDesempenho(aluno* Aluno){

    //printf("Nota: %lf | Frequencia: %lf\n", Aluno->nota, Aluno->frequencia);

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
    aluno alunos[30];
    for(int c = 0; c < 30; c++){
        printf("Insira a nota do aluno %d: ", c+1);
        scanf("%lf", &alunos[c].nota);
        printf("Insira a frequencia do aluno %d em porcentagem : ", c+1);
        scanf("%lf", &alunos[c].frequencia);
        printf("\n");
    }

    printf("\nSITUAÇÃO DOS ALUNOS:\n");

    for(int c = 0; c < 30; c++){
        printf("\nAluno: %d\n", c + 1);
        validarDesempenho(&alunos[c]);
        printf("\n");
    }

    return 0;
}