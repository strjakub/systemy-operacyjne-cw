//
// Created by jakub on 3/15/22.
//

#include <ctype.h>
#include "mylib.h"

void error(char * msg){
    printf("%s", msg);
    exit(0);
}

ArrayOfBlocks createArrayOfBlocks(int max_size){
    struct ArrayOfBlocks array;

    array.blocks = (struct Block**) calloc(max_size, sizeof(struct Block));
    array.size = 0;

    return array;
}

Block createBlock(int size){
    struct Block block;

    block.info = (char*) calloc(size, sizeof(char));

    return block;
}

void removeBlock(ArrayOfBlocks array, int index){
    if(index < 0)
        error("Bad index");
    if(index >= array.size)
        error("Bad index");

    int i = index + 1;
    while(i < array.size){
        array.blocks[i - 1] = array.blocks[i];
        array.blocks[i] = NULL;
        i = i + 1;
    }
}

int addBlockToArray(ArrayOfBlocks array, Block block){
    array.blocks[array.size] = &block;
    return array.size;
}

void tmp_create(){
    system("touch -c tmp.txt");
}

void tmp_remove(){
    system("rm -f tmp.txt");
}

void wc(const char* from, const char* to){
    char * command = calloc(100, sizeof(char));

    strcpy(command, "wc ");
    strcat(command, from);
    strcat(command, " > ");
    strcat(command, to);

    system(command);
}

int isNumber(char* s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
        if (!isdigit(s[i]))
            return 0;
    return 1;
}

int count(ArrayOfBlocks array, const char* from){
    wc(from, "tmp.txt");

    FILE* file = fopen("tmp.txt", "r");

    if(!file)
        error("error?");

    char* rows = calloc(10, sizeof(char));
    char* words = calloc(10, sizeof(char));
    char* bytes = calloc(10, sizeof(char));
    char* name = calloc(50, sizeof(char));
    fscanf(file, "%s %s %s %s", rows, words, bytes, name);
    fclose(file);
    char* info = calloc(80, sizeof(char));
    strcpy(info, rows);
    strcat(info, " ");
    strcat(info, words);
    strcat(info, " ");
    strcat(info, bytes);
    strcat(info, " ");
    strcat(info, name);
    Block newBlock = createBlock(strlen(info));
    newBlock.info = info;
    int x = addBlockToArray(array, newBlock);
    fclose(fopen("tmp.txt", "w"));

    return x;
}