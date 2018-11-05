#include "../include/BinaryTree.h"
#include "../include/Exception.h"
#include "../include/ArrayList.h"
#include "../include/Typedefs.h"
#include <stdio.h>
#include <stdlib.h>

#define BCast(Tree) ((HBinaryTree)Tree)

typedef struct Node
{
	Object leftSon;
	Object rightSon;
	int value;
}*Node;

typedef struct Leaf
{
	char caracter;
	int frequency;
}*Leaf;

typedef struct HBinaryTree
{
	Node* root;
	uint32_t nodes;
}*HBinaryTree;

static Node newNode(void);
static Leaf newLeaf(char caracter, int frequency);
static int compare(Object obj1, Object obj2);

static int compare(Object obj1, Object obj2)
{

}

BinaryTree newBinaryTree(void)
{
	HBinaryTree tree = NULL;


	try
	{
		tree = (HBinaryTree)malloc(sizeof(struct HBinaryTree));
		if(tree != NULL)
		{
			tree->root = (Node*)malloc(sizeof(Node));
			if(tree->root == NULL)
			{
				throw(__MemoryAllocationException__);
			}
			tree->nodes = 0;
		}
	}
	catch(MemoryAllocationException)
	{

	}

	return tree;
}

static Node newNode(void)
{
	Node new_node = NULL;

	try
	{
		new_node = (Node)malloc(sizeof(struct Node));
		if(new_node != NULL)
		{
			new_node->leftSon = NULL;
			new_node->rightSon = NULL;
			new_node->value = None;
		}
		else
		{
			throw(__MemoryAllocationException__);
		}
	}
	catch(MemoryAllocationException)
	{

	}

	return new_node;
}

static Leaf newLeaf(char caracter, int frequency)
{
	Leaf leaf = NULL;

	try
	{
		leaf = (Leaf)malloc(sizeof(struct Leaf));
		if(leaf != NULL)
		{
			leaf->caracter = caracter;
			leaf->frequency = frequency;
		}
		else
		{
			throw(__MemoryAllocationException__);
		}
	}catch(MemoryAllocationException)
	{

	}

	return leaf;
}

Symbol newSymbol(char caracter, int frequency)
{
	Symbol symb = NULL;

	try
	{
		symb = (Symbol)malloc(sizeof(struct Symbol));
		if(symb != NULL)
		{
			symb->caracter = caracter;
			symb->frequency = frequency;
		}
		else
		{
			throw(__MemoryAllocationException__);
		}
	}
	catch(MemoryAllocationException)
	{

	}

	return symb;
}

BinaryTree newBinaryTreeHuffman(ArrayList symbolList)
{
	uint32_t symbols;
	uint32_t i;
	Node z;
	Symbol x, y;
	BinaryTree tree;

	tree = newBinaryTree();

	symbols = getListSize(symbols);
	z = newNode();

	for(i = 0; i < symbols - 1; i++)
	{
		x = removeTopList(symbolList);
		y = removeTopList(symbolList);
		z->leftSon = x;
		z->rightSon = y;
		z->value = x->frequency + y->frequency;
		insertSorted(symbolList, z, compare);
	}

	BCast(tree)->root = removeTopList(symbolList);

	return tree;
}


