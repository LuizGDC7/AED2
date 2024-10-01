#include "calculator.h"
#include "planilha.h"
#include <stdio.h>

int main(){
    data *valores = create_data();
    calculadora* calc = create_calculadora();

    int qtdLinhas, qtdColunas;
    printf("Quantas linhas [objetos diferentes] voce usara?\n>");
    scanf(" %d%*c", &qtdLinhas);
    printf("Quantas colunas [informacao por objeto] voce usara?\n>");
    scanf(" %d%*c", &qtdColunas);

    double** matrix = NULL;
    matrix = (double**) malloc((qtdLinhas + 5) * sizeof(double*));
    for(int c = 0; c < qtdLinhas; c++){
        matrix[c] = (double*) malloc((qtdColunas + 5) * sizeof(double));
    }

    char *leitura = leituraSuja(matrix, qtdLinhas, qtdColunas);

    char* preprocessado = preprocesso(leitura, qtdLinhas);

    //printf("preprocessado:\n%s\n", preprocessado);

    char* transcrito = transcicao(matrix, qtdLinhas, preprocessado);

    printf("\n%s\n", transcrito);

    read_data(valores, transcrito);

    //show_c_list(valores);

    printf("\nVALUE IS: %.3lf\n", solve(valores));

    kill_data(valores);
    kill_calculadora(calc);
    free(leitura);
    free(preprocessado);
    free(transcrito);

    return 0;
}