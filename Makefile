OBJS = src/ArrayList.c src/BinaryTree.c src/main.c src/Exception.c
CC = gcc
OBJ_NAME = main

all: $(OBJS)
	$(CC) $(OBJS)  -o $(OBJ_NAME) 