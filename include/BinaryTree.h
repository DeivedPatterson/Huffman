#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include "../include/ArrayList.h"
#include <stdint.h>


typedef void* BinaryTree;

typedef struct Symbol
{
	char caracter;
	int32_t frequency;
}*Symbol;


BinaryTree newBinaryTreeHuffman(ArrayList symbolList);
BinaryTree newBinaryTree(void);
Symbol newSymbol(char caracter, int32_t frequency);
void PrintBinaryHuffmanPreOrder(BinaryTree tree);



#endif