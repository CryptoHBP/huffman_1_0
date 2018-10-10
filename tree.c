#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "heap.h"

//creates new tree setting the frequency and the byte to the node
tree* create_new_tree(long long unsigned freq, void* byte)
{
	tree *new_tree = (tree*) malloc(sizeof(tree));
	new_tree->freq = freq;
	new_tree->byte = malloc(sizeof(unsigned char));
	*((unsigned char*)new_tree->byte) = *((unsigned char*)byte);
	new_tree->right = NULL;
	new_tree->left = NULL;
	return new_tree;
}
// creates a tree with the huffman propriety of being a parent with the sum of two frequencies
tree* create_huff_tree(tree *left, tree *right)
{
	tree *new_tree = (tree*) malloc(sizeof(tree));
	new_tree->left = left;
	new_tree->right = right;
	new_tree->freq = left->freq + right->freq;
	new_tree->byte = malloc(sizeof(unsigned char));
	*((unsigned char*)new_tree->byte) = 42;
	return new_tree;
}
//checks if the tree is empty
int is_empty(tree *hufftree)
{
	if(hufftree == NULL)return 1;
	else return 0;
}
/* takes the first element of the heap of trees and swaps with the last one 
to do the dequeue, than decreases size and returns the first element*/
tree* dequeuehp(heap *heap)
{
    tree *item = heap->tree[1];
    heap->tree[1] = heap->tree[heap->size];
    heap->size--;
    heapfy(heap,1);
    return item;
}
/*will print the huffman tree into file checking if '*' and/or '\\' are children elements
of the hufftree. If they are, than print then as '\\'*/
void print_pre_order(tree *hufftree, FILE *file_out)
{
	
	if(!is_empty(hufftree))
	{
		if(is_leaf(hufftree))
		{
			if((*(unsigned char*)hufftree->byte == '*' || *(unsigned char*)hufftree->byte == '\\')) fputc('\\',file_out);;
			fputc((*(unsigned char*)hufftree->byte),file_out);
			return;
		}
		fputc((*(unsigned char*)hufftree->byte),file_out);
		print_pre_order(hufftree->left,file_out);
		print_pre_order(hufftree->right,file_out);
	}
	
}
//checks if its a leaf
unsigned int is_leaf(tree *tree)
{
	return (tree->right == NULL && tree->left ==NULL);
}
/*will build the hufftre. First it decreases the two elements wiht smallest frequncies,
then calls enqueueparent to make a node of huffman tree. Returns the hufftree*/
tree* build_hufftree(tree *hufftree, heap *heap)
{
	tree *auxtree = NULL;
	tree *auxtree2 = NULL;
	while(heap->begin < heap->size)
    {
  	    auxtree = dequeuehp(heap);

	    auxtree2 = dequeuehp(heap);

		hufftree = enqueueparent(heap,auxtree,auxtree2);	  
    } 
    return hufftree;
}

// sets bit to 1
unsigned char set_bit(unsigned char c, unsigned int i)
{
	unsigned char mask = 1 << i;
	return mask | c;
}