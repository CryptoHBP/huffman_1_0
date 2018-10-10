#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "compress.h"
#include "tree.h"
#include "hash_tree.h"
#include "hash_table.h"
#include "interface.h"

//creates an empty decompressed tree
decompress_tree* create_empty_decompress_tree()
{
	return NULL;
}

//creates a node to the decompressed tree, with byte and its left and right children
decompress_tree* create_decompress_tree(void* byte, decompress_tree *left, decompress_tree *right)
{
	decompress_tree *new_decompress_tree = (decompress_tree*) malloc(sizeof(decompress_tree));
	new_decompress_tree->byte = malloc(sizeof(unsigned char));
	(*(unsigned char*)new_decompress_tree->byte) = (*(unsigned char*)byte);
	new_decompress_tree->left =	left;
	new_decompress_tree->right = right;
	return new_decompress_tree;
}

/*recreates the tree of the file by checking if the byte is equivalent to a parent.
If yes, then create a node pointing to NULL. If not, first check if the byte is the escape
character, if yes then walk to the next byte, if not, create a new node with the byte*/ 

decompress_tree* add(decompress_tree *dt,unsigned char byte, FILE *file_in)
{
	byte = fgetc(file_in);
	if(byte == '*')
	{
		dt = create_decompress_tree(&byte, NULL, NULL);	
		dt->left = add(dt,byte,file_in);
		dt->right = add(dt,byte,file_in);
	}
	else
	{
		if(byte == '\\') byte = fgetc(file_in);
		dt = create_decompress_tree(&byte, NULL, NULL);
	}
	return dt;
}

//gets the size of the entry file by walking on it.Then does rewind to teh begin of the file. Returns size
unsigned int get_file_size(FILE* file_in)
{
	unsigned int filesize = 0;
	unsigned char filebyte;
	while(fscanf(file_in,"%c",&filebyte) != EOF) filesize++;
	rewind(file_in);
	return filesize; 
}

/*Will walk the whole compressed file until its size reaches one,and walk in the decompressed tree until it finds a leaf.
Then prints the byte of the leaf in the new decompressed file. Lastly, it checks the last byte until the size if trash before printing it to teh new file*/
decompress_tree* search_in_tree(decompress_tree *dt,FILE* file_in,FILE* file_out,unsigned int filesize,unsigned int trash)
{
	decompress_tree* root = dt;
	int index;
	unsigned char byte;
	while(fscanf(file_in,"%c",&byte) != EOF)
	{
		index = 7;
		if(filesize >= 1)
		{
			while(index >= 0)
			{
				if(dt->left == NULL && dt->right == NULL) 
				{
					fputc((*(unsigned char*)dt->byte),file_out);
					dt = root;
				}
				if(is_bit_i_set(byte,index)) dt = dt->right;
				else dt = dt -> left;
				index--;
			}
		}
		else
		{
			while(index >= trash)
			{
				if(dt->left == NULL && dt->right == NULL) 
				{
					fputc((*(unsigned char*)dt->byte),file_out);
					dt = root;
				}
				if(is_bit_i_set(byte,index)) dt = dt->right;
				else dt = dt -> left;
				index--;
			}
		}
		filesize--;
	}
}

/*opens two files, the compressed one to read and a new decompressed one to write.
Gets file size, then decreases by the two first bytes(trash and tree size), and then decreases the whole tree.
Lastly, calls search in tree to write the decompressed file*/
void decompress(char filename[])
{
	FILE* file_in;
	FILE *file_out;
	file_in = fopen(filename,"rb");
	file_out = fopen("out","wb");

	decompress_tree *dt= create_empty_decompress_tree();
	decompress_tree *root= create_empty_decompress_tree();
	decompress_tree *result = create_empty_decompress_tree();
	unsigned char byte,trash = 0,first,second;
	unsigned short treesize = 0;
	unsigned int filesize;

	filesize = get_file_size(file_in);

	first = fgetc(file_in);

	trash = first;
	treesize = first;

	second = fgetc(file_in);

	treesize = treesize << 11;
	treesize = treesize >> 3;
	treesize += second;

	trash = trash >> 5;
	
	dt = add(dt, 0, file_in);

	filesize -= 2;
	filesize -= treesize;

	search_in_tree(dt,file_in,file_out,filesize,trash);
}