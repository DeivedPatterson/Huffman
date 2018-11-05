#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include "../include/ArrayList.h"

typedef void* BinaryTree;

typedef struct Symbol
{
	char caracter;
	int frequency;
}*Symbol;


BinaryTree newBinaryTreeHuffman(ArrayList symbolList);
BinaryTree newBinaryTree(void);
Symbol newSymbol(char caracter, int frequency);




#endif