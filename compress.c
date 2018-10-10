#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "compress.h"
#include "tree.h"
#include "hash_tree.h"
#include "hash_table.h"

//checks if bit is set
int is_bit_i_set(unsigned int compbyte,unsigned int i)
{
	unsigned int mask = 1<<i;
	return mask & compbyte;
}

/*it will set bits to fill the new byte according to the compressed bits of the element of the entry file.
It will send a byte starting with zero, but in the will return it probably set.The next calls, it will receive the byte again
but it will be treated as previous in order to continue to set that entire byte to print in the output file.
This way, in case of the geral byte not being fully set in the current call, it will continue setting in the next call.
It also considers if it happens that the compressed byte doesn't end in the current call, so the function will continue to set it 
in the next call*/

unsigned char print_compress(unsigned int compbyte, unsigned char *indexprevius,unsigned char byteprevious, FILE *file_out, unsigned int height)
{
	unsigned char byte = 0;
	unsigned int pos_byte_comp;
	unsigned char indexgeral;
	pos_byte_comp = height;
	pos_byte_comp--;


	indexgeral = *indexprevius; //updates de geral index
	while(pos_byte_comp >= 0 && indexgeral >= 0)// will only stop if the index of the compbyte and the index of geral byte are both zero
	{
		if(is_bit_i_set(compbyte,pos_byte_comp)) byte = set_bit(byte,indexgeral);// Setting current byte in geral byte

		if(pos_byte_comp > 0) pos_byte_comp--;// will decrease the index of the compacted byte in order to "walk" on it
		else					              //if the index of the compacted byte reaches zero, updates the index geral and updates the geral byte				
		{										
			if(indexgeral > 0) indexgeral--;//decreases geral byte until zero
			else indexgeral = 7; 		 //when it reaches zero, sets it to seven again 
			*indexprevius = indexgeral;  
			return byte + byteprevious; // returns the geral byte after setting bits to it
		}								
		if(indexgeral > 0) indexgeral--;// decreases geral index
		else						//when it reaches zero, sets to seven again.		
		{									
			indexgeral = 7;                
			byte += byteprevious; // updates geral byte 
			fputc(byte,file_out); // prints geral byte on file
			*indexprevius = indexgeral;// updates geral index
			byte = 0; 	// updates geral byte to zero
			byteprevious = 0; // updates previous byte to zero
		}
	}
}

/*reads the entry file again to start checking the bytes and see its compressed version
in the second hash by calling the function print_compress. It will only write full compressed bytes
if the geral index(index of new byte with compressed bits) ends, that meaning, if it reaches 7*/
unsigned int compress(hash_tree *hashtree,char filename[],FILE *file_out)
{
	unsigned char key = 0;
	unsigned char *index_geral_freq;
	unsigned char filebyte;
	unsigned int trash,*first;
	unsigned char byte = 0;
	first = malloc(sizeof(unsigned char));
	*first = 0;
	index_geral_freq = malloc(sizeof(unsigned char));
	*index_geral_freq = 7;

	FILE *file_in;
	file_in = fopen(filename, "rb"); //opens entry file again
	
	while(fscanf(file_in,"%c",&filebyte) != EOF)
	{

		key = create_index(&filebyte); // gets the index of the byte to the second hash

		byte = print_compress(hashtree->trees[key]->path_bits,index_geral_freq,byte,file_out,hashtree->trees[key]->height);				
				
		if(*index_geral_freq == 7)
		{
			fputc(byte,file_out);// prints the full compressed byte in new file
			byte = 0;// sets byte to zero to start to fill it again
		}		
	}
	if(*index_geral_freq != 7)fputc(byte,file_out);  //it's necessary to print the last byte in here in case of trash 

	rewind(file_out); // goes to the beginning of the output file. Necessary to set the trash and tree size

	trash = *index_geral_freq + 1;    
	*first = trash << 13;                  
	
	fclose(file_in); //closes the entry file
	return *first; // returns a pointer to the value of trash
}
