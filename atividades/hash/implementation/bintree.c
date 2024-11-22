#include "bintree.h"

node *create_node(int val){
    node *temporario = NULL;
    do{
        temporario = (node*) malloc(1*sizeof(node));
    } while (temporario == NULL);
    temporario->l_son = NULL;
    temporario->r_son = NULL;
    temporario->informacoes.chave = val;
    return temporario;
}

void create_b_tree(btree *arvore){
    arvore->root = NULL;
}

void btree_insert(btree *arvore, node *endereco){ //filhos a esquerda sempre sao menores, a direita sao iguais ou maiores
    node *temp1 = NULL; //futuro pai
    node *temp2 = arvore->root;
    while(temp2 != NULL){ //procura um lugar adequado para o filho, se sua chave for menor que uma chave atual, continuamos procurando pela esquerda, do contrario, procuramos pela direita ate encontrarmos um node vazio
        temp1 = temp2;
        if(endereco->informacoes.chave < temp2->informacoes.chave){
            temp2 = temp2->l_son;
        }else{
            temp2 = temp2->r_son;
        }
    }
    endereco->father = temp1;
    if(temp1 == NULL){
        arvore->root = endereco;
    }else if(endereco->informacoes.chave < temp1->informacoes.chave){
        temp1->l_son = endereco;
    } else{
        temp1->r_son = endereco;
    }
}

void transplant(btree *arvore, node *end1, node *end2){ //trocamos os pais de end1 e end2 um pelo outro
    if(end1->father == NULL){ //estamos trocando a raiz pr outro node
        arvore->root = end2;
    } else if(end1 == (end1->father->l_son)){ //ou seja, end1 é menor que seu pai
        end1->father->l_son = end2;
    } else{
        end1->father->r_son = end2;
    }

    if(end2 != NULL){ //troca simples e direta do pai de end2 pelo end1
        end2->father = end1->father;
    }

    /*
        lembrando que aqui nao fazemos nenhuma comparacao, apenas fazemos a troca
    */
}

node *tree_minimun(node *endereco){
    if(endereco != NULL){
        node *temporario = endereco;
        while(temporario->l_son != NULL){
            temporario = temporario->l_son;
        }
        return temporario;
    }else{
        return NULL;
    }
    
}

node *tree_maximun(node *endereco){
    if(endereco != NULL){
        node *temporario = endereco;
        while(temporario->r_son != NULL){
            temporario = temporario->r_son;
        }
        return temporario;
    }else{
        return NULL;
    }
}

node *tree_sucessor(node *endereco){
    if(endereco != NULL){
        if(endereco->r_son != NULL){ //ou seja, endereco tem filhos 
            return tree_minimun(endereco->r_son);
        } 
        node *temporario = endereco->father;
        node *temporario2 = endereco;
        while(temporario != NULL && temporario2 == temporario->r_son){
            temporario2 = temporario;
            temporario = temporario->father;
        }
        return temporario;
    }else{
        return NULL;
    }
    

    /*
    A jogada do while é voltar ate que o filho seja o filho esquerdo do pai, ou seja, ele é maior que o pai, e então por transitividade, ele é maior que o endereco 
    */
    
    /*
    O sucessor de endereco e o menor no do filho direito do endereco
    */
}

node *tree_predecessor(node *endereco){
    if(endereco != NULL){
        if(endereco->l_son != NULL){
            return tree_maximun(endereco->l_son);
        }
        node *temporario = endereco->father;
        node *temporario2 = endereco;
        while(temporario != NULL && temporario2 == temporario->l_son){
            temporario2 = temporario;
            temporario = temporario->father;
        }
        return temporario;
    }else{
        return NULL;
    }
    
}

void btree_delete_node(btree *arvore, node *endereco){ //tudo depende se endereco tem filhos
    /*
    substituimos o endereco pelo seu sucessor presente em sua subarvore direita
    */
    if(endereco != NULL){
        if(endereco->l_son == NULL){ //aqui e em baixo nos simplesmente elevamos os filhos para ficarem no lugar do pai
            transplant(arvore, endereco, endereco->r_son); 
        }else if(endereco->r_son == NULL){ //nao tem filhos
            transplant(arvore, endereco, endereco->l_son);
        } else { //VOLTA AQUI FDP
            node *temporario = tree_minimun(endereco->r_son);
            if(temporario->father != endereco){
                transplant(arvore, temporario, temporario->r_son);
                temporario->r_son = endereco->r_son;
                temporario->r_son->father = temporario;
            }
            transplant(arvore, endereco, temporario);
            temporario->l_son = endereco->l_son;
            temporario->l_son->father = temporario;
        }
        free(endereco);
    }
}

node *tree_search(node *endereco, int chave){
    if(endereco != NULL){
        node *temporario = endereco;
        while(temporario != NULL && temporario->informacoes.chave != chave){
            if(chave < temporario->informacoes.chave){
                temporario = temporario->l_son;
            }else{
                temporario = temporario->r_son;
            }
        }
    return temporario;
    } else{
        return NULL;
    }
}

void linear_walking_sort(node *endereco){
    if(endereco != NULL){
        linear_walking_sort(endereco->l_son);
        printf("%d\n", endereco->informacoes.chave);
        linear_walking_sort(endereco->r_son);
    }
}

void cut_tree(node *endereco){
    if(endereco != NULL){
        cut_tree(endereco->l_son);
        cut_tree(endereco->r_son);
        free(endereco);
    }
}

int bt_menu(btree *arvore){
    int opcao, valor;
    node *temporario = NULL;
    printf("\n\nEscolha uma opcao:\n\n1-Inserir node\n2-Deletar node\n3-Procurar menor node\n4-Procurar maior node\n5-Procurar existencia de um node com uma chave\n6-Mostrar o sucessor de um node\n7-Mostrar o predecessor de um node\n8-Walking sort\n9-Sair\n\n>> ");
    do{
        scanf("%d%*c", &opcao);
    } while (opcao < 1 || opcao > 9);
    
    switch(opcao){
        case 1:
            printf("Insira o valor: ");
            scanf("%d", &valor);
            temporario = create_node(valor);
            btree_insert(arvore, temporario);
            break;
        
        case 2:
            printf("Insira o valor a se deletar: ");
            scanf("%d", &valor);
            btree_delete_node(arvore, tree_search(arvore->root, valor));
            break;
        
        case 3:
            temporario = tree_minimun(arvore->root);
            if(temporario != NULL){
                printf("O menor node tem valor: %d | endereco: %p\n", temporario->informacoes.chave, temporario);    
            }else{
                printf("O menor node tem valor: %p | endereco: %p\n", temporario, temporario);
            }
            break;
        
        case 4:
            temporario = tree_maximun(arvore->root);
            if(temporario != NULL){
                printf("O maior node tem valor: %d | endereco: %p\n", temporario->informacoes.chave, temporario);    
            }else{
                printf("O maior node tem valor: %p | endereco: %p\n", temporario, temporario);
            }
            break;
        
        case 5:
            printf("Insira o valor: ");
            scanf("%d", &valor);
            temporario = tree_search(arvore->root, valor);
            if(temporario != NULL){
                printf("Endereco encontrado: %p\n", temporario);
            }else{
                printf("Endereco nao encontrado!\n");
            }
            break;
        
        case 6:
            printf("Insira o valor: ");
            scanf("%d", &valor);
            temporario = tree_sucessor(tree_search(arvore->root, valor));
            if(temporario != NULL){
                printf("Valor: %d | endereco: %p\n", temporario->informacoes.chave, temporario);
            }else{
                printf("O valor nao possui sucessor!\n");
            }
            break;
        
        case 7:
            printf("Insira o valor: ");
            scanf("%d", &valor);
            temporario = tree_predecessor(tree_search(arvore->root, valor));
            if(temporario != NULL){
                printf("Valor: %d | endereco: %p\n", temporario->informacoes.chave, temporario);
            }else{
                printf("O valor nao possui predecessor!\n");
            }
            break;

        case 8:
            linear_walking_sort(arvore->root);
            break;
        
        case 9:
            cut_tree(arvore->root);
            return 0;
    }

    return 1;
}