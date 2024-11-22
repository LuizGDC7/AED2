#include "../header/hash.h"


void warnAndAbortion(char* warn){
    if(warn == NULL){
        printf("aborting...\n");
    }else{
        printf("%s\n", warn);
    }
    fflush(stdout);
    abort();
}

void hashInit(hash* hashTable){

    hashTable->tree = NULL;
    hashTable->size = 0;
}

void hashCreate(hash* hashTable, int positions){
    if(hashTable != NULL){
        if(hashTable->tree == NULL){
            hashTable->tree = (btree*) malloc(positions * sizeof(btree));
            hashTable->size = positions;

            if(hashTable->tree == NULL){
                warnAndAbortion("Failed at hashCreate");
            }

            btree* arv = hashTable->tree;
            for(int c = 0; c < positions; c++){
                create_b_tree(&arv[c]);
            }

        }
    }
}

void destroyHash(hash* hashTable){
    if(hashTable != NULL){
        int limit = hashTable->size;
        for(int c = 0; c < limit; c++){
            node* no = hashTable->tree[c].root;
            cut_tree(no);
        }
    }
}

int hashFunction(int index, hash* hashTable){

    if(hashTable == NULL){
        warnAndAbortion("NULL hashTable at hashFunction");
    }

    if(index == 0 && hashTable->size == 0){
        warnAndAbortion("index and hashTable size are 0");
    }
    return index % hashTable->size;
}

void insertHash(int value, hash* hashTable){
    
    if(hashTable == NULL){
        warnAndAbortion("NULL hashTable at insertHash");
    }

    int index = hashFunction(value, hashTable);

    btree_insert(&(hashTable->tree[index]), create_node(value));
}

node* searchHash(int value, hash* hashTable){
    
    if(hashTable == NULL){
        warnAndAbortion("NULL hashTable at insertHash");
    }

    int index = hashFunction(value, hashTable);
    node* no = (hashTable->tree[index]).root;

    if(no != NULL){
        int passos = 1;
        node *temporario = no;
        while(temporario != NULL && temporario->informacoes.chave != value){
            if(value < temporario->informacoes.chave){
                temporario = temporario->l_son;
            }else{
                temporario = temporario->r_son;
            }
            passos++;
        }
        temporario == NULL ? printf("Valor nao encontrado\n") : printf("Valor %d encontrado, levaram %d passo[s] (contagem a partir do numero 1)\n", value, passos);
    return temporario;
    } else{
        return NULL;
    }

}

