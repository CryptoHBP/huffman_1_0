#ifndef  HASH_TREE_H
#define HASH_TREE_H
typedef struct hash_tree hash_tree;
typedef struct tree_element tree_element;

struct tree_element
{
	void* byte;//element from hufftree
	unsigned int height;//height of node
	unsigned int path_bits;//path of bits in the tree
};

struct hash_tree
{
	tree_element *trees[257];//array of pointers to tree_element
};

hash_tree* create_hash_tree();

void put_from_tree(hash_tree *hashtree, void* byte,unsigned int compbyte,unsigned int h);


#endif