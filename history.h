/* Name: Keegan Vanstone
   Lab 2 simple shell

   This is a header file for the "history.c" file
*/

#include "dataStructures.h"

#define HISTSIZE 5

void print_history(struct Block *historyDb);

void delete_old(struct Block *historyDb);

void add_history(char *command, struct Block *historyDb);
