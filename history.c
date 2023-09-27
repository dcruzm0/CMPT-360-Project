/* Name: Keegan Vanstone
   Lab 2 simple shell
   
   This program contains the functions related to when the user in the shell types in "history"
   It includes a function to print all the commands stored in the history database, add a command 
   that was entered by the user and remove the oldest command in history (a.k.a the first one) to 
   Store a new one.
*/

#include "history.h"

int hSIZE = 0;

/* This function will print all the commands that are stored in the history database */
void print_history(struct Block *historyDb){

  /* print all the entries in the database */
  for (int i = 0; i < hSIZE; i++) {
    printf("%d.   %s %s\n", i + 1, historyDb[i].key, historyDb[i].value);
  }

}

/* This program will remove the first entry in the history data structure to make room for new commands to be stored */
void delete_old(struct Block *historyDb){

  /* loop through the database until the last entry, move everything back to overwrite the oldest entry */
  for(int i = 0; i < hSIZE - 1; i++) {
    strcpy(historyDb[i].key, historyDb[i + 1].key);
    strcpy(historyDb[i].value, historyDb[i + 1].value);
  }

  /* set the last entry to the NULL character to make it empty */
  strcpy(historyDb[4].key, "\0");
  strcpy(historyDb[4].value, "\0");

  /* decrease the total size by 1 */
  hSIZE -= 1;
}

/* This program takes the command as a string and the history data structure and will store that command in the array */
void add_history(char *command, struct Block *historyDb){

  int num;
  char val1[21],val2[21];

  /* check if the database is full, and if it is, delete the oldest entry */
  if (HISTSIZE == hSIZE) {
    delete_old(historyDb);
  }

  /* try to split the user entry into 2 components */
  num = sscanf(command, "%s %s", val1, val2);

  /* if only 1 word was entered, set the other half to NULL and add it to the database and increment the size */
  if (num == 1) {
    strcpy(val2, "\0");
    strcpy(historyDb[hSIZE].key, val1);
    strcpy(historyDb[hSIZE].value, val2);
    hSIZE += 1;
  }

  /* copy each command into the database and increment the size */
  else {
    strcpy(historyDb[hSIZE].key, val1);
    strcpy(historyDb[hSIZE].value, val2);
    hSIZE += 1;
  }

}
