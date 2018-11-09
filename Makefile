OBJS = src/ArrayList.c src/BinaryTree.c src/main.c src/Exception.c src/Ultility.c
CC = gcc
OBJ_NAME = main

all: $(OBJS)
	$(CC) $(OBJS)  -o $(OBJ_NAME) -lm #-DDEBUG_ON