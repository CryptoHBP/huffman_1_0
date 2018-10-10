#ifndef DECOMPRESS_H
#define DECOMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "compress.h"
#include "tree.h"
#include "hash_tree.h"
#include "hash_table.h"
#include "interface.h"

typedef struct decompress_tree decompress_tree;

struct decompress_tree
{
	void* byte;
	decompress_tree *left;
	decompress_tree *right;
};

decompress_tree* create_empty_decompress_tree();

decompress_tree* create_decompress_tree(void* byte, decompress_tree *left, decompress_tree *right);

decompress_tree* add(decompress_tree *dt,unsigned char byte, FILE *file_in);

unsigned int get_file_size(FILE* file_in);

decompress_tree* search_in_tree(decompress_tree *dt,FILE* file_in,FILE* file_out,unsigned int filesize,unsigned int trash);

void decompress(char filename[]);

#endif