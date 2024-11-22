#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

// Estrutura de nó da árvore de Huffman
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// Estrutura de MinHeap (Árvore Binária)
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Função auxiliar para criar um novo nó da árvore de Huffman
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Função auxiliar para criar um MinHeap de capacidade dada
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Funções para manter a estrutura do MinHeap
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Criação da árvore de Huffman
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Função para armazenar os códigos de Huffman em um array
void storeCodes(struct MinHeapNode* root, int arr[], int top, char **huffmanCodes) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, huffmanCodes);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, huffmanCodes);
    }

    if (isLeaf(root)) {
        huffmanCodes[(unsigned char)root->data] = (char *)malloc(top + 1);
        for (int i = 0; i < top; i++) {
            huffmanCodes[(unsigned char)root->data][i] = arr[i] + '0';
        }
        huffmanCodes[(unsigned char)root->data][top] = '\0';
    }
}

// Função para gravar os códigos binários no arquivo binário
void writeCompressedData(FILE *outputFile, const char *inputFilename, char **huffmanCodes) {
    FILE *inputFile = fopen(inputFilename, "rb");
    if (!inputFile) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    unsigned char buffer = 0;
    int bitCount = 0;

    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        char *code = huffmanCodes[(unsigned char)ch];
        for (int i = 0; code[i] != '\0'; i++) {
            buffer = buffer << 1 | (code[i] - '0');
            bitCount++;
            if (bitCount == 8) {
                fputc(buffer, outputFile);
                buffer = 0;
                bitCount = 0;
            }
        }
    }

    // Caso tenha bits pendentes
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        fputc(buffer, outputFile);
    }

    fclose(inputFile);
}

// Função principal de compressão
void compressFile(const char *inputFilename, const char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "rb");
    if (!inputFile) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    int freq[256] = {0};
    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        freq[(unsigned char)ch]++;
    }
    fclose(inputFile);

    char data[256];
    int freqData[256];
    int dataSize = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[dataSize] = (char)i;
            freqData[dataSize] = freq[i];
            dataSize++;
        }
    }

    struct MinHeapNode *root = buildHuffmanTree(data, freqData, dataSize);
    int arr[MAX_TREE_HT], top = 0;
    char *huffmanCodes[256] = {NULL};
    storeCodes(root, arr, top, huffmanCodes);

    FILE *outputFile = fopen(outputFilename, "wb");
    fwrite(freq, sizeof(int), 256, outputFile);
    writeCompressedData(outputFile, inputFilename, huffmanCodes);
    fclose(outputFile);
}

// Função de descompressão
void decompressFile(const char *inputFilename, const char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "rb");
    FILE *outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile) {
        fprintf(stderr, "Erro ao abrir arquivos.\n");
        return;
    }

    int freq[256];
    fread(freq, sizeof(int), 256, inputFile);

    char data[256];
    int freqData[256];
    int dataSize = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[dataSize] = (char)i;
            freqData[dataSize] = freq[i];
            dataSize++;
        }
    }

    struct MinHeapNode *root = buildHuffmanTree(data, freqData, dataSize);
    struct MinHeapNode *current = root;
    int bit;

    unsigned char buffer;
    while (fread(&buffer, sizeof(char), 1, inputFile)) {
        for (int i = 7; i >= 0; i--) {
            bit = (buffer >> i) & 1;
            current = bit ? current->right : current->left;
            if (isLeaf(current)) {
                fputc(current->data, outputFile);
                current = root;
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <comprimir|descomprimir> <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "comprimir") == 0) {
        compressFile(argv[2], argv[3]);
    } else if (strcmp(argv[1], "descomprimir") == 0) {
        decompressFile(argv[2], argv[3]);
    } else {
        fprintf(stderr, "Opção inválida: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
