#include <stdio.h>
#include <stdlib.h>
#include "../include/ArrayList.h"
#include "../include/Typedefs.h"
#include "../include/BinaryTree.h"
#include <stdint.h>

#define MAX_BUFFER_STRING 	4096L


static int compare(Object obj1, Object obj2);




static int compare(Object obj1, Object obj2)
{
	Symbol s1 = (Symbol)obj1;
	Symbol s2 = (Symbol)obj2;

	return s1->frequency - s2->frequency;
}

int main(int argc, char const *argv[])
{
	ArrayList symbolList;
	BinaryTree treeHuffman;
	char* buffer = NULL;
	int32_t n, i;
	char caracter;
	int32_t frequency = 0;
	Symbol s;


	buffer = (char*)calloc(MAX_BUFFER_STRING, sizeof(char));
	symbolList = newArrayList(-1);

	puts("Entre com o texto a ser compactado");
	fgets(buffer, MAX_BUFFER_STRING, stdin);

	puts("Entre com o tamanho da tabela");
	scanf("%i", &n);
	puts("Entre com cada simbolo e sua frequência");
	for(i = 0; i < n; i++)
	{
		getchar();
		scanf("%c", &caracter);
		scanf("%i", &frequency);
		insertSorted(symbolList, newSymbol(caracter, frequency), compare);
	}

	treeHuffman = newBinaryTreeHuffman(symbolList);
	//HuffmanCodec(treeHuffman, buffer);
	BuildTableSymbol(treeHuffman, symbolList);
	//PrintBinaryHuffmanPosOrder(treeHuffman);

	return 0;
}