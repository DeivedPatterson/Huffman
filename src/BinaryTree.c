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
	struct TreeNode* father;
	Object data;
	uint32_t edgeLeft;
	uint32_t edgeRight;
	uint32_t edgeFather;
}*TreeNode;

typedef struct HBinaryTree
{
	TreeNode* root;
	uint32_t nodes;
}*HBinaryTree;

static TreeNode newNode(Object data);
static int compare(Object obj1, Object obj2);
static void PosOrder(TreeNode* root);
static void PreOrder(TreeNode* root, ArrayList list);

static int compare(Object obj1, Object obj2)
{
	TreeNode n1 = (TreeNode)obj1;
	TreeNode n2 = (TreeNode)obj2;

	printf("n1: %i, n2: %i\n", ((Symbol)(n1->data))->frequency ,((Symbol)(n2->data))->frequency);

	/*
	if(((Symbol)(n2->data))->frequency > ((Symbol)(n1->data))->frequency)
	{
		return 1;
	}
	else if(((Symbol)(n2->data))->frequency < ((Symbol)(n1->data))->frequency)
	{
		return -1;
	}
	*/


	return (((Symbol)(n1->data))->frequency - ((Symbol)(n2->data))->frequency);
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
			new_node->father = NULL;
			new_node->data = data;
			new_node->edgeLeft = 0;
			new_node->edgeRight = 0;
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
	TreeNode p;
	Symbol temp;
	BinaryTree tree;
	ArrayList nodeList;
	bool father = true;

	tree = newBinaryTree();
	nodeList = newArrayList(INFINITE);

	foreach_ArrayList(temp, symbolList)
	{
		insertBottomList(nodeList, newNode(temp));
	}

	symbols = getListSize(symbolList);

	for(i = 0; i < symbols - 1; i++)
	{
		z = newNode(newSymbol(None, 0));
		x = (TreeNode)removeTopList(nodeList);
		y = (TreeNode)removeTopList(nodeList);
		z->edgeLeft = 0;
		z->edgeRight = 1;
		z->leftSon = x;
		z->rightSon = y;
		z->edgeFather = !father;
		father = !father;
		x->father = z;
		y->father = z;
		//printf("x: %i, y: %i\n", ((Symbol)(x->data))->frequency, ((Symbol)(y->data))->frequency);
		((Symbol)z->data)->frequency = ((Symbol)(x->data))->frequency + ((Symbol)(y->data))->frequency;
		insertSorted(nodeList, z, compare);

		foreach_ArrayList(p, nodeList)
		{
			printf("%i ", ((Symbol)(p->data))->frequency);
		}
		puts(" ");
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

static void PreOrder(TreeNode* root, ArrayList list)
{

	if((*root)->leftSon != NULL && (*root)->rightSon != NULL) 
	{
		printf("Direita %i, Esquerda %i, frequency %i\n", (*root)->edgeLeft, (*root)->edgeRight, ((Symbol)((*root)->data))->frequency);
		PreOrder(&(*root)->leftSon, list);
		PreOrder(&(*root)->rightSon, list);
	}
	else
	{
		insertSorted(list, *root, compare);
	}
}
//DCCACADEACCCCCBCEBBBD
uint32_t HuffmanCodec(BinaryTree tree, const char* txt)
{
	uint32_t i;

	
}

ArrayList BuildTableSymbol(BinaryTree tree, ArrayList symbolList)
{
	ArrayList leaves;
	TreeNode z;
	Symbol s;
	TreeNode scroll;
	uint32_t p = 0;
	uint32_t i;
	uint32_t size;

	leaves = newArrayList(INFINITE);

	PreOrder(BCast(tree)->root, leaves);

	size = getListSize(leaves);
	while(not isEmpty(leaves))
	{	
		z = removeTopList(leaves);
		scroll = z->father;
		//printf("%c", ((Symbol)((z)->data))->caracter);
		p = 0;
		while(scroll != NULL)
		{
			//printf("%i ", ((Symbol)((scroll)->data))->frequency);
			p = (p << 1) | scroll->edgeFather;
			scroll = scroll->father;
		}
		printf("%i\n", p);
	}
}