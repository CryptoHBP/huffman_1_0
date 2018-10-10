#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "tree.h"
typedef struct tree tree;
typedef struct heap heap;

struct tree
{
	void* byte;//element
	long long unsigned freq;//frequency
	tree *left;
	tree *right;
};

unsigned int is_leaf(tree *tree);

tree* create_new_tree(long long unsigned freq, void* byte);

tree* create_huff_tree(tree *left, tree *right);

int is_empty(tree *hufftree);

tree* dequeuehp(heap *heap);

void print_pre_order(tree *hufftree, FILE *file_out);

tree* build_hufftree(tree *hufftree, heap *heap);

unsigned char set_bit(unsigned char c, unsigned int i);

#endif