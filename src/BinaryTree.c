#include "../include/BinaryTree.h"
#include "../include/Exception.h"
#include "../include/ArrayList.h"
#include "../include/Typedefs.h"
#include "../include/Ultility.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
static void BuildTable(TreeNode* root, const ArrayList table, uint32_t w);

static int compare(Object obj1, Object obj2)
{
	TreeNode n1 = (TreeNode)obj1;
	TreeNode n2 = (TreeNode)obj2;

	return (((Symbol)(n1->data))->frequency - ((Symbol)(n2->data))->frequency);
}

static int compareSymbol(Object obj1, Object obj2)
{
	Symbol s1 = (Symbol)obj1;
	Symbol s2 = (Symbol)obj2;

	return s1->frequency - s2->frequency;
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

static SymbolCode newSymbolCode(char caracter, uint32_t code)
{
	SymbolCode symbCode = NULL;

	try
	{
		symbCode = (SymbolCode)malloc(sizeof(struct SymbolCode));
		if(symbCode != NULL)
		{
			symbCode->caracter = caracter;
			symbCode->code = code;
		}
		else
		{
			throw(__MemoryAllocationException__);
		}
	}
	catch(MemoryAllocationException)
	{

	}

	return symbCode;
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

	for(i = 0; i < (symbols) - 1; i++)
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

void HuffmanCodec(ArrayList table, const char* txt)
{
	int i;
	SymbolCode symbCode;
	char v[10];

	for(i = 0; isgraph(txt[i]) != 0; i++)
	{
		foreach_ArrayList(symbCode, table)
		{
			if(symbCode->caracter == txt[i])
			{
				ToBinary(symbCode->code, v);
				printf("%s", v);
				memset(v, 0, 10);
			}
		}
	}
	puts(" ");
}

static void BuildTable(TreeNode* root, const ArrayList table, uint32_t w)
{

	if((*root)->leftSon == NULL && (*root)->rightSon == NULL)
	{
		char caracter;

		caracter = ((Symbol)((*root)->data))->caracter;
		insertBottomList(table, newSymbolCode(caracter, w));

		return;
	}

	BuildTable(&(*root)->leftSon, table, (w << 1) | false );
	BuildTable(&(*root)->rightSon, table, (w << 1) | true );
}

ArrayList BuildSymbolTable(BinaryTree tree)
{
	ArrayList table;
	SymbolCode symbCode;
	char v[10];

	table = newArrayList(INFINITE);

	BuildTable(BCast(tree)->root, table, 0);

	#ifdef DEBUG_ON
	foreach_ArrayList(symbCode, table)
	{
		ToBinary(symbCode->code, v);
		printf("caracter: %c code: %s\n", symbCode->caracter, v);
	}
	#endif
	
	return table;
}

ArrayList BuildFrequencyTable(const char* txt)
{
	uint32_t i, j, k;
	char caracter;
	int32_t frequency;
	ArrayList fTable;
	char* mark;
	uint32_t size;
	bool isMark = false;

	fTable = newArrayList(INFINITE);
	size = strlen(txt) + 1;
	mark = (char*)calloc(size, sizeof(char));

	for(i = 0; isgraph(txt[i]) != 0; i++)
	{
		frequency = 0;
		for(k = 0; k < size; k++)
		{
			if(txt[i] == mark[k])
			{
				isMark = true;
			}
		}
		
		if(!isMark)
		{
			for(j = 0; isgraph(txt[j]) != 0; j++)
			{
				if(txt[i] == txt[j])
				{
					mark[i] = txt[i];
					frequency += 1;
				}
			}
			caracter = txt[i];
			insertSorted(fTable, newSymbol(caracter, frequency), compareSymbol);
		}

		isMark = false;
		
	}

	return fTable;
}