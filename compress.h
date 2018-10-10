#ifndef COMPRESS_H
#define COMPRESS_H
#include "tree.h"
#include "hash_tree.h"
#include "hash_table.h"
#include <gtk/gtk.h>

int is_bit_i_set(unsigned int comp,unsigned int i);

unsigned char print_compress(unsigned int compbyte, unsigned char *indexprevius,unsigned char byteprevious, FILE *file_out,unsigned int height);

void put_trash(FILE *file_out, unsigned int trash);

unsigned int compress(hash_tree *hashtree,char filename[], FILE *file_out);

#endif 