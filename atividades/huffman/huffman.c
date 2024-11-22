#include "./huffman.h"

#define MAX_TREE_HT 10000

char* readFile(const char* nome_arquivo, int* size) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    char *conteudo = NULL;
    long tamanho = 0;

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    // Vai para o final do arquivo
    fseek(arquivo, 0, SEEK_END);
    // Obtém o tamanho do arquivo
    tamanho = ftell(arquivo);
    
    // Volta para o início do arquivo
    fseek(arquivo, 0, SEEK_SET);
    *size = tamanho;

    // Aloca espaço para a string (tamanho + 1 para o caractere nulo)
    conteudo = (char*) malloc((tamanho + 1) * sizeof(char));
    if (conteudo == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        fclose(arquivo);
        return NULL;
    }

    // Lê todo o conteúdo do arquivo para a string
    fread(conteudo, sizeof(char), tamanho, arquivo);
    conteudo[tamanho] = '\0';  // Adiciona o caractere nulo ao final da string

    fclose(arquivo);
    return conteudo;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size){
    struct MinHeapNode *left, *right, *top;

    
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {

        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[], int top){

    // Assign 0 to left edge and recur
    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root)) {

        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)

{
    // Construct Huffman Tree
    struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;

    printCodes(root, arr, top);
}

void destroyInput(input* in){
    if(in == NULL)
        return;
    if(in->stringInput != NULL)
        free(in->stringInput);
    if(in->stringComposition != NULL)
        free(in->stringComposition);
    if(in->frequency != NULL)
        free(in->frequency);
}

void riseWarning(char* warning){
    printf("%s\n", warning);
    fflush(stdout);
    abort();
}

int* countCharacters(char* stringInput, int size){
    if(stringInput == NULL){
        riseWarning("NULL STRING INPUT");
    }

    int* count = NULL;
    count = (int*) calloc(257, sizeof(int));
    if(count == NULL){
        riseWarning("Failed to malloc in countCharacters");
    }

    for(int c = 0; c < size; c++){
        count[(int) stringInput[c]]++;
    }

    return count;
}

input* wrapData(char* stringInput, int size){
    if(stringInput == NULL){
        riseWarning("NULL STRING INPUT");
    }
    
    input* data = NULL;
    data = (input*) malloc(sizeof(input));
    if(data == NULL){
        riseWarning("Failed to malloc in wrapData");
    }

    int* qtdReference = countCharacters(stringInput, size);
    int notZero = 0;

    for(int c = 0; c < 256; c++){
        if(qtdReference[c] > 0){
            notZero++;
        }
    }

    char* charactersComposition = NULL;
    int* charactersCount = NULL;

    charactersComposition = (char*) malloc(1 + notZero * sizeof(char));
    charactersCount = (int*) malloc(1 + notZero * sizeof(int));

    if(charactersComposition == NULL || charactersCount == NULL){
        riseWarning("Failed at malloc in wrapData");
    }

    for(int c = 0, d = 0; c < 256; c++){
        if(qtdReference[c] > 0){
            charactersComposition[d] = (char) c;
            charactersCount[d] = qtdReference[c];
            d++;
        }
    }
    
    charactersComposition[notZero] = '\0';
    data->stringComposition = charactersComposition;
    data->frequency = charactersCount;
    data->stringSize = size;
    data->stringInput = stringInput;
    data->characterCompositionQtd = notZero;

    return data;
}