#include <stdio.h>
#include <stdlib.h>
#include "../include/ArrayList.h"
#include "../include/Typedefs.h"
#include "../include/BinaryTree.h"
#include "../include/Exception.h"
#include <stdint.h>

#define MAX_BUFFER_STRING 	4096L

int main(int argc, char const *argv[])
{
	ArrayList symbolList;
	ArrayList symbolCode;
	BinaryTree treeHuffman;
	char* buffer = NULL;
	char size[10];
	uint32_t textSize;
	FILE* input;



	buffer = (char*)calloc(MAX_BUFFER_STRING, sizeof(char));
	symbolList = newArrayList(-1);

	FileOpen(input, "text.txt", "r");
	fgets(buffer, MAX_BUFFER_STRING, input);
	printf("%s\n", buffer);


	symbolList = BuildFrequencyTable(buffer);

	treeHuffman = newBinaryTreeHuffman(symbolList);
	symbolCode = BuildSymbolTable(treeHuffman);
	HuffmanCodec(symbolCode, buffer);
	#ifdef DEBUG_ON
	PrintBinaryHuffmanPosOrder(treeHuffman);
	#endif
	
	return 0;
}