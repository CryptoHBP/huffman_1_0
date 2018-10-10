#include <stdio.h>
#include <stdlib.h>
#include "change_structure.h"
#include "heap.h"
#include "hash_table.h"
#include "tree.h"
#include "hash_tree.h"


/*sends the bytes of the hash to the heap using enqueue*/
void hashtoheap(heap *heap,hash_table *hashtable)
{
	int i;
	for(i = 0;i < 256;i++)
	{
	    if(hashtable->table[i]!=NULL) 
	    {
			enqueue(heap,hashtable->table[i]->freqbyte,hashtable->table[i]->byte);//first the frequency then the byte
	    }
	}
}

/* sends the elements of the tree to the second hash. 
Also does shift bit to set the compbyte(compacted byte) and it becomes the said compacted byte
of that element of the tree, the compbyte is stored at the second hash along with its element */

void treetohash(tree *hufftree, hash_tree *hashtree, unsigned int compbyte, unsigned int *size, unsigned int h)
{
	(*size)++;
	if(is_leaf(hufftree))
	{
		put_from_tree(hashtree,hufftree->byte,compbyte,h);
		return;
	}
	else
	{
		compbyte = compbyte << 1;
		treetohash(hufftree->left,hashtree,compbyte,size,h+1);
		compbyte+=1;
		treetohash(hufftree->right,hashtree,compbyte,size,h+1);
		compbyte-=1;
		compbyte = compbyte >> 1;
	}

	return;
}
