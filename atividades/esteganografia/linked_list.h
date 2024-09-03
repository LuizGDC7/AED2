#ifndef C_LINKED_LIST

#define C_LINKED_LIST

typedef struct _dados{
    int valor;
} dados;

typedef struct _node{
    dados informacoes;
    struct _node *sucessor;
    struct _node *predecessor; 
} node;

typedef struct _c_linked_list{
    int tamanho;
    node *inicio;
    node *fim;
} c_linkedl;

c_linkedl create_c_list();

void kill_c_list(c_linkedl *list);

node *create_node(int value);

void insert_c_list(c_linkedl *list, node *endereco); //insercao pela cauda

void del_c_list_element(c_linkedl *list, node *endereco, int dar_free);

void show_c_list(c_linkedl *list);

int opc_exc(c_linkedl *list);

#endif