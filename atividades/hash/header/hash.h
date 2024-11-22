#ifndef __HASHT__

#define __HASHT__

#include "./bintree.h"

typedef struct hash {
    btree *tree;
    int size;
} hash;

void warnAndAbortion(char* warn);

void hashInit(hash* hashTable);

void hashCreate(hash* hashTable, int positions);

void destroyHash(hash* hashTable);

int hashFunction(int index, hash* hashTable);

void insertHash(int value, hash* hashTable);

node* searchHash(int value, hash* hashTable);

#endif