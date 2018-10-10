#include <stdio.h>
#include <stdlib.h>
#include "hash_tree.h"
#include "hash_table.h"

//creates hash 
hash_tree* create_hash_tree()
{	
	int i;
	hash_tree *new_hash_tree = (hash_tree*) malloc(sizeof(hash_tree));
	for(i = 0;i < 256;++i)
	{
		new_hash_tree->trees[i] = NULL;
	}
	return new_hash_tree;

}
//put in the hash_tree the elements of the tree, the serie of compressed bits and the height of that node in the hufftree
void put_from_tree(hash_tree *hashtree, void* byte, unsigned int compbyte,unsigned int h)
{
	unsigned int index;
	index = create_index(byte);

	tree_element *new_element = (tree_element*) malloc(sizeof(tree_element));
	new_element->byte = malloc(sizeof(unsigned char));
	(*(unsigned char*)new_element->byte) = (*(unsigned char*)byte);
	new_element->path_bits = compbyte;
	new_element->height = h;
	hashtree->trees[index] = new_element;	
}
