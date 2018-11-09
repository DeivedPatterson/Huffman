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

typedef struct SymbolCode
{
	char caracter;
	uint32_t code;
}*SymbolCode;

BinaryTree newBinaryTreeHuffman(ArrayList symbolList);
ArrayList BuildSymbolTable(BinaryTree tree);
BinaryTree newBinaryTree(void);
Symbol newSymbol(char caracter, int32_t frequency);
void PrintBinaryHuffmanPosOrder(BinaryTree tree);
void HuffmanCodec(ArrayList table, const char* txt);
ArrayList BuildFrequencyTable(const char* txt);

#endif