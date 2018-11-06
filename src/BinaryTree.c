#include "../include/BinaryTree.h"
#include "../include/Exception.h"
#include "../include/ArrayList.h"
#include "../include/Typedefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>

#define BCast(Tree) ((HBinaryTree)Tree)

typedef struct TreeNode
{
	struct TreeNode* leftSon;
	struct TreeNode* rightSon;
	Object data;
}*TreeNode;

typedef struct HBinaryTree
{
	TreeNode* root;
	uint32_t nodes;
}*HBinaryTree;

static TreeNode newNode(Object data);
static int compare(Object obj1, Object obj2);
static void PosOrder(TreeNode* root);


static int compare(Object obj1, Object obj2)
{
	TreeNode n1 = (TreeNode)obj1;
	TreeNode n2 = (TreeNode)obj2;

	return ((Symbol)(n1->data))->frequency - ((Symbol)(n2->data))->frequency;
}

BinaryTree newBinaryTree(void)
{
	HBinaryTree tree = NULL;


	try
	{
		tree = (HBinaryTree)malloc(sizeof(struct HBinaryTree));
		if(tree != NULL)
		{
			tree->root = (TreeNode*)malloc(sizeof(TreeNode));
			if(tree->root != NULL)
			{
				*(tree->root) = NULL;
				tree->nodes = 0;
			}
			else
			{
				throw(__MemoryAllocationException__);
			}
		}
	}
	catch(MemoryAllocationException)
	{

	}

	return tree;
}

static TreeNode newNode(Object data)
{
	TreeNode new_node = NULL;

	try
	{
		new_node = (TreeNode)malloc(sizeof(struct TreeNode));
		if(new_node != NULL)
		{
			new_node->leftSon = NULL;
			new_node->rightSon = NULL;
			new_node->data = data;
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

Symbol newSymbol(char caracter, int32_t frequency)
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
	TreeNode x,y,z;
	Symbol temp;
	BinaryTree tree;
	ArrayList nodeList;

	tree = newBinaryTree();
	nodeList = newArrayList(-1);

	foreach_ArrayList(temp, symbolList)
	{
		insertBottomList(nodeList, newNode(temp));
	}

	symbols = getListSize(symbolList);

	for(i = 0; i < symbols - 1; i++)
	{
		z = newNode(newSymbol(None, None));
		x = (TreeNode)removeTopList(nodeList);
		y = (TreeNode)removeTopList(nodeList);
		z->leftSon = x;
		z->rightSon = y;
		((Symbol)z->data)->frequency = ((Symbol)(x->data))->frequency + ((Symbol)(y->data))->frequency;
		insertSorted(nodeList, z, compare);
	}

	*(BCast(tree)->root) = removeTopList(nodeList);

	return tree;
}

static void PosOrder(TreeNode* root)
{
	if(*root != NULL)
	{
		PosOrder(&((*root)->leftSon));
		PosOrder(&((*root)->rightSon));

		if(((Symbol)((*root)->data))->caracter == None && ((Symbol)((*root)->data))->frequency != None)
		{
			printf("Caracter: %s | Frequency: %i\n", "None", ((Symbol)((*root)->data))->frequency);
		}
		else
		{
			printf("Caracter: %c | Frequency: %i\n", ((Symbol)((*root)->data))->caracter, ((Symbol)((*root)->data))->frequency);
		}
	}
}

void PrintBinaryHuffmanPosOrder(BinaryTree tree)
{
	PosOrder(BCast(tree)->root);
}

static uint32_t PreOrder(TreeNode* root, char caracter, uint32_t bit)
{
	static uint32_t code;

	if((*root) != NULL) 
	{
		//code = (code << 1) | bit;
		printf("%c %i\n", ((Symbol)((*root)->data))->caracter, bit);
		PreOrder(&(*root)->leftSon, caracter, 0);
		PreOrder(&(*root)->rightSon, caracter, 1);
	}

	return bit;
}
//DCCACADEACCCCCBCEBBBD
uint32_t HuffmanCodec(BinaryTree tree, const char* txt)
{
	uint32_t i;

	
	PreOrder(BCast(tree)->root, 0, 0);
	
}