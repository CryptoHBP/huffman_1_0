#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "hash_table.h"
#include "heap.h"
#include "tree.h"	
#include "hash_table.h"
#include "compress.h"
#include "change_structure.h"
#include "interface.h"
#include "decompress.h"
#define MAX_SIZE 1000000


void start(char filename[],GtkWidget* status)
{
	int i;
	unsigned char filebyte,byte = 0;
	hash_table *hash = create_hash_table();
	heap *heap = create_heap();
	hash_tree* hash2 = create_hash_tree();
	tree *hufftree = NULL;
	unsigned int *size, index,header, aux = 0;
  unsigned char trash = 0, sizef = 0;
	FILE *file_in;
	FILE *file_out;
	char filename_out[MAX_SIZE];
  int ind = 7,walk =15;
	size = malloc(sizeof(unsigned int));
	*size = 0;

  file_in = fopen(filename, "rb");

  // reading the file and puting its elements in the first hash
	while(fscanf(file_in,"%c", &filebyte) != EOF)
	{
		put(hash, &filebyte);
	}
	fclose(file_in);
	
  // sends the elements of the hash to the heap
  hashtoheap(heap,hash);

  //calls heapify to sort the heap
	for(i=(heap->size)/2;i>=1;i--)
  {
    heapfy(heap,i);
  }    
     
  //creates the huffman tree
  hufftree = build_hufftree(hufftree, heap);

  //sends elemenst os the hufftree to the hashtree
  treetohash(hufftree,hash2,0,size,0);

  // names the new file which will possess the compressed bytes
  index = 0;
  while(filename[index] != '\0')
  {
  	filename_out[index] = filename[index];
  	index++;
  }
  index=0;
  while(filename_out[index] != '\0') index++;
  index--;
  filename_out[index+2] = '\0';
  filename_out[index+1] = 'f';
 	filename_out[index] = 'f';
  filename_out[index-1] = 'u';
 	filename_out[index-2] = 'h';
 	filename_out[index-3] = '.';
  	
  file_out = fopen(filename_out,"wb");
	
  //prints two empty bytes in file
	fputc(byte,file_out);
	fputc(byte,file_out);

 	//prints the tree in file 
 	print_pre_order(hufftree,file_out);
	// compress, this function returns the value of the trash
  header = compress(hash2,filename,file_out);

  //the sum of the trash and the tree size will be the header of the compressed file
  header = header + (*size);

  /* these two whiles are to divide o unsigned int header to two unsigned char 
  and then put in file*/
  while(walk >= 8)
  {
    if(is_bit_i_set(header,walk)) trash = set_bit(trash,ind);
    walk--;
    ind--;
  }
  ind = 7;
  walk = 7;
  while(walk >= 0)
  {
    if(is_bit_i_set(header,walk)) sizef = set_bit(sizef,ind);
    walk--;
    ind--;
  }
  fputc(trash,file_out);
  fputc(sizef,file_out);
  fclose(file_out);
  gtk_spinner_stop(GTK_SPINNER(status));  	
}
