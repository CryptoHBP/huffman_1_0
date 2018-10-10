#ifndef CHANGE_STRUCTURE_H
#define CHANGE_STRUCTURE_H
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "hash_table.h"
#include "tree.h"
#include "hash_tree.h"



void hashtoheap(heap *heap,hash_table *hashtable);//elements of the first hash to the tree
void treetohash(tree *hufftree, hash_tree *hashtree, unsigned int compbyte, unsigned int *size,unsigned int h);//elements of the hufftree to the second hash

#endif