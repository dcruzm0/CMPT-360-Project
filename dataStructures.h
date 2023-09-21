#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Block{
  char key[21];//Unique value in array
  char value[21];//Not unique value assigned to a key
};

int getData(char *key, struct Block * block);
/*This function gets the position of the key
 *Input: string key we are searching for, blocks array of Block
 */

void setData(char * key, char * value, struct Block * block);
/*This function sets the data in the block. It sets the first free spot
 *Input: string key, string value, Block pointer to array of Block
 */

void removeData(char * key, struct Block * blocks);
/*This function removes a key and value from the array
 *Input: string key we remove, block array of Block
 */

void printAll(struct Block * block);
/*This function prints of all the keys and values in the array
 *Input: blocks array of Block
 *
 */

void printBlock(char * key, struct Block *  blocks);
/*This function prints a specific Block with the key
 *Input: key string we want, blocks array of Block
 *
 */

void searchBlock(char * key, struct Block * blocks);
/*This function checks if a block with a key exists
 *Input: key key of block we want, block array of Blocks
 *
 */


  
