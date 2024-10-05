#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define INITIAL_SIZE 10  // Tamanho inicial da pilha

typedef struct {
    int topo;
    int capacidade;
    double *itens;  
} Pilha;

// Funções para manipular a pilha
void inicializaPilha(Pilha *p) {
    p->topo = -1;
    p->capacidade = INITIAL_SIZE;
    p->itens = (double *)malloc(p->capacidade * sizeof(double));
    if (p->itens == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        exit(1);
    }
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void redimensionaPilha(Pilha *p, int novaCapacidade) {
    double *novaPilha = (double *)realloc(p->itens, novaCapacidade * sizeof(double));
    if (novaPilha == NULL) {
        printf("Erro: Falha na realocação de memória!\n");
        free(p->itens);
        exit(1);
    }
    p->itens = novaPilha;
    p->capacidade = novaCapacidade;
}

void push(Pilha *p, double valor) {
    // Se a pilha estiver cheia, dobramos a capacidade
    if (p->topo == p->capacidade - 1) {
        redimensionaPilha(p, p->capacidade * 2);
    }
    p->itens[++(p->topo)] = valor;
}

double pop(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->itens[(p->topo)--];
    } else {
        printf("Erro: Pilha vazia!\n");
        exit(1); // Encerramos o programa em caso de erro
    }
}

void liberaPilha(Pilha *p) {
    free(p->itens);
}

// Função para avaliar uma expressão em notação polonesa posfixa
double avaliarRPN(char *expressao) {
    Pilha pilha;
    inicializaPilha(&pilha);
    char *token = strtok(expressao, " ");

    while (token != NULL) {
        // Se for um número, empurramos na pilha
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&pilha, atof(token));
        }
        // Se for um operador, executamos a operação
        else {
            double b = pop(&pilha);
            double a = pop(&pilha);

            switch (token[0]) {
                case '+':
                    push(&pilha, a + b);
                    break;
                case '-':
                    push(&pilha, a - b);
                    break;
                case '*':
                    push(&pilha, a * b);
                    break;
                case '/':
                    if (b != 0) {
                        push(&pilha, a / b);
                    } else {
                        printf("Erro: Divisão por zero!\n");
                        liberaPilha(&pilha);
                        exit(1);
                    }
                    break;
                case '^':
                    push(&pilha, pow(a, b));
                    break;
                default:
                    printf("Erro: Operador desconhecido '%s'\n", token);
                    liberaPilha(&pilha);
                    exit(1);
            }
        }

        token = strtok(NULL, " ");
    }

    double resultado = pop(&pilha);
    if (!pilhaVazia(&pilha)) {
        printf("Erro: Pilha não está vazia após avaliação.\n");
        liberaPilha(&pilha);
        exit(1);
    }
    liberaPilha(&pilha);
    return resultado;
}

int main() {
    char expressao[1000];

    printf("Digite a expressão em notação polonesa posfixada (use espaço entre os elementos):\n");
    if (fgets(expressao, sizeof(expressao), stdin) == NULL) {
        printf("Erro ao ler a expressão.\n");
        return 1;
    }

    // Remove o '\n' da string de entrada
    expressao[strcspn(expressao, "\n")] = 0;

    // Verifica se a expressão não está vazia
    if (strlen(expressao) == 0) {
        printf("Erro: Expressão vazia.\n");
        return 1;
    }

    double resultado = avaliarRPN(expressao);

    printf("Resultado: %.2lf\n", resultado);

    return 0;
}
