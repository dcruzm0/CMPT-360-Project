/*----------------------------------------------------------------------------
 * Name: Mark D'Cruz
 * Lab 1
 * This is the dataStructures.c file
  ---------------------------------------------------------------------------*/
#include "dataStructures.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int MAX_ARRAY_SIZE = 50;
int MAX_NAME_SIZE = 20;
int SIZE = 0;

int getData(char* key, struct Block * blocks){
  /*This function gets the position of the key
   *Input: string key we are searching for, blocks array of Block
   */
  for(int i = 0; i != SIZE + 1; i++){
    if (strcmp(blocks[i].key, key) == 0){
      return i;
    }
  }
  //If key does not exist
  return 51;
}

void setData(char * i_key, char * i_value, struct Block * blocks){
  /*This function sets the data in the block. It sets the first free spot
   *Input: string key, string value, Block pointer to array of Block
   */
  //Checks if structures is full
  if(SIZE == MAX_ARRAY_SIZE){
    printf("\n\nData Structure is too full\n\n");
    return;
  }
  //Gets position
  int a = getData(i_key, blocks);
  //If key does exist
  if(a != 51){
    strcpy(blocks[a].key, i_key);
    strcpy(blocks[a].value, i_value);
    return;
  }
  //Set first free block
  strcpy(blocks[SIZE].key, i_key);
  strcpy(blocks[SIZE].value, i_value);
  SIZE = SIZE + 1;
  return;
}

void removeData(char * i_key, struct Block * blocks){
  /*This function removes a key and value from the array
   *Input: string key we remove, block array of Block
   */
  //Searches for keys position
  int a = getData(i_key, blocks);
  //Key does not exist
  if(a == 51){
    printf("Data not found\n");
    return;
  }
  //Sets key and value to null character
  strcpy(blocks[a].key, "\0");
  strcpy(blocks[a].value, "\0");
  //Moves other entries down
  for(int i = a; i == SIZE; i++){
    strcpy(blocks[i].key, blocks[i+1].key);
    strcpy(blocks[i].value, blocks[i+1].value);
  }
  //Sets last entry to null character
  strcpy(blocks[SIZE].key, "\0");
  strcpy(blocks[SIZE].value, "\0");
  //Decrement total size
  SIZE = SIZE - 1;
  return;
}

void printAll(struct Block * blocks){
  /*This function prints of all the keys and values in the array
   *Input: blocks array of Block
   *
   */
  for(int i = 0; i != SIZE ; i++){
    printf("\nKey: %s, Value: %s\n", blocks[i].key, blocks[i].value);
  }
}

void printBlock(char * key, struct Block * blocks){
  /*This function prints a specific Block with the key
   *Input: key string we want, blocks array of Block
   *
   */
  //Searches for position
  int i = getData(key, blocks);
  //Key does not exist
  if(i == 51){
    printf("Value does not exist");
    return;
  }
  printf("\nKey: %s, Value: %s\n", blocks[i].key, blocks[i].value);
  return;
}

void searchBlock(char * key, struct Block * blocks){
  /*This function checks if a block with a key exists
   *Input: key key of block we want, block array of Blocks
   *
   */
  int i = getData(key, blocks);
  if(i == 51){
    printf("Key does not exist");
    return;
  }
  printf("Key does exist");
  return;
}
  
