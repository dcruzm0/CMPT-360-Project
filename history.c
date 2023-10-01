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
void print_history(struct Entry *historyDb){

  /* print all the entries in the database */
  for (int i = 0; i < hSIZE; i++) {
    printf("%d.   %s\n", i + 1, historyDb[i].command);
  }
}

/* This program will remove the first entry in the history data structure to make room for new commands to be stored */
void delete_old(struct Entry *historyDb){

  /* loop through the database until the last entry, move everything back to overwrite the oldest entry */
  for(int i = 0; i < hSIZE - 1; i++) {
    strcpy(historyDb[i].command, historyDb[i + 1].command);
    
  }

  /* set the last entry to the NULL character to make it empty */
  strcpy(historyDb[4].command, "\0");
  

  /* decrease the total size by 1 */
  hSIZE -= 1;
}

/* This program takes the command as a string and the history data structure and will store that command in the array */
void add_history(char *cmd, struct Entry *historyDb){


  /* check if the database is full, and if it is, delete the oldest entry */
  if (HISTSIZE == hSIZE) {
    delete_old(historyDb);
  }

  /* copy each command into the database and increment the size */
  strcpy(historyDb[hSIZE].command, cmd);
  hSIZE += 1;

}
