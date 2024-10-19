#include "bintree.h"

int main(){

    btree arvore;
    btree *root = &arvore;
    create_b_tree(root);

    int digitos = 1, valor, opcao, setimoDigito = -1;

    do {
        printf("\n\nj0. Sair\n1. Inserir número\n2. Mostrar em ordem\nEscolha uma opção: ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                printf("Digite o número para inserir: ");
                scanf(" %d", &valor);
                if(valor < 0 || valor > 9){
                    continue;
                }
                btree_insert(root, create_node(valor));
                if(digitos == 7)
                    setimoDigito = valor;
                digitos++;
                break;

            case 2:
                printf("Números em ordem: ");
                linear_walking_sort(root->root);
                printf("\n");
                break;


            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0 && digitos < 12);

    //linear_walking_sort(root->root);

    btree_delete_node(root, tree_search(root->root, setimoDigito));

    printf("\n\nSetimo digito e': %d\n", setimoDigito);
    printf("Numeros do CPF ordenados sem o setimo digito: ");
    linear_walking_sort(root->root);

    cut_tree(root->root);

    return 0;
}