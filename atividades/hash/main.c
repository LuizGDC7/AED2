#include "./header/hash.h"

int main(int argc, char *argv[]){

    if(argc != 2){
        warnAndAbortion("Incorrect entry");
    }

    FILE *arquivo;
    hash tabela;
    hashInit(&tabela);
    hashCreate(&tabela, 997);
    int val = 0, opcao = 0;

    arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1; // Encerra com erro
    }

    while (fscanf(arquivo, "%d", &val) == 1) { // Lê cada número
        insertHash(val, &tabela);
    }

    do{
        printf("\n\nEscolha uma opcao:\n\n0 - Sair\n1 - Procurar valor\n");
        scanf(" %d", &opcao);
        if(opcao){
            printf("Digite valor: ");
            scanf(" %d", &val);

            searchHash(val, &tabela);
        }

    } while (opcao == 1);
    
    int ocupado = 0;

    for(int c = 0; c < tabela.size; c++){
        if(tabela.tree[c].root != NULL){
            ocupado++;
        }
    }

    printf("\n\nDo total de %d posicoes:\n%d sao ocupadas\n%d sao desocupadas\n", tabela.size, ocupado, tabela.size - ocupado);

    
    destroyHash(&tabela);
    fclose(arquivo);

    return 0;
}