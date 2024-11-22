#ifndef _HEAP_

#define _HEAP_
#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeapNode {

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child of this node
    struct MinHeapNode *left, *right;
} MinHeapNode;

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
typedef struct MinHeap {

    // Current size of min heap
    unsigned size;

    // capacity of min heap
    unsigned capacity;

    // Array of minheap node pointers
     MinHeapNode** array;
} MinHeap;

MinHeapNode* newNode(char data, unsigned freq);

MinHeap* createMinHeap(unsigned capacity);

void swapMinHeapNode( MinHeapNode** a,  MinHeapNode** b);

void minHeapify( MinHeap* minHeap, int idx);

int isSizeOne( MinHeap* minHeap);

MinHeapNode* extractMin( MinHeap* minHeap);

void insertMinHeap( MinHeap* minHeap,  MinHeapNode* minHeapNode);

void buildMinHeap( MinHeap* minHeap);

void printArr(int arr[], int n);

int isLeaf( MinHeapNode* root);

MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);


#endif