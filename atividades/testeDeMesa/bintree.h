#ifndef _BINTREE_

#define BINTREE

#include <stdlib.h>
#include <stdio.h>

typedef struct _dados{
    int chave;
} dados;

typedef struct _node{
    struct _node *father;
    struct _node *l_son;
    struct _node *r_son;
    dados informacoes;
} node;

typedef struct _bintree{
    node *root;
} btree;

node *create_node(int val);

void create_b_tree(btree *arvore);

void btree_insert(btree *arvore, node *endereco);

void transplant(btree *arvore, node *end1, node *end2);

node *tree_minimun(node *endereco);

node *tree_maximun(node *endereco);

node *tree_sucessor(node *endereco);

node *tree_predecessor(node *endereco);

void btree_delete_node(btree *arvore, node *endereco);

node *tree_search(node *endereco, int chave);

void linear_walking_sort(node *endereco);

void cut_tree(node *endereco);

int bt_menu(btree *arvore);

#endif