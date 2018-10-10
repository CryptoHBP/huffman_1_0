#ifndef HEAP_H
#define HEAP_H
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "heap.h"
typedef struct heap heap;
typedef struct tree tree;
struct heap
{
    int begin;
    int size;
    tree *tree[256];
};

heap* create_heap();//creates heap

void enqueue(heap *heap, long long unsigned freq, void* byte);//enqueue elements that aren't trees

tree* enqueueparent(heap *heap,tree* left, tree* right);//enqueue elements that are trees

int get_parent_i(heap *heap,int i);

int get_left_i(heap *heap,int i);

int get_right_i(heap *heap,int i);

void heapfy(heap *heap,int i);//min heapify for the parent go minor than the frequncy of the children trees

#endif