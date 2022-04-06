//
// Created by jakub on 3/14/22.
//

#ifndef ZAD1_2_MYLIB_H
#define ZAD1_2_MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Block{
    char* info;
} Block;

typedef struct ArrayOfBlocks{
    Block** blocks;
    int size;
    int max_size;
} ArrayOfBlocks;

ArrayOfBlocks createArrayOfBlocks(int max_size);
//void removeArrayOfBlocks(ArrayOfBlocks* array);
Block createBlock(int size);
void removeBlock(ArrayOfBlocks array, int index);
int addBlockToArray(ArrayOfBlocks array, Block block);

void tmp_create();
void tmp_remove();

void wc(const char* from, const char* to);
int isNumber(char* s);
int count(ArrayOfBlocks array, const char* from);
void error1(char * msg);

#endif //ZAD1_2_MYLIB_H
