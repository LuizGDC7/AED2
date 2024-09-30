#ifndef _PLANILHA_

#define _PLANILHA_

#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* preprocesso(char *input, int maxRows);

char* transcicao(double **matrix, int maxRows, char* input);

char* leituraSuja(double **matrix, int qtdLinhas, int qtdColunas);



#endif