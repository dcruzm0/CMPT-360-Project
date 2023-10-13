/* Name: Keegan Vanstone
   Lab 2 simple shell

   This is a header file for the "history.c" file
*/


struct Entry {
  char command[50];
};

#define HISTSIZE 5

void print_history(struct Entry *historyDb);

void delete_old(struct Entry *historyDb);

void add_history(char *cmd, struct Entry *historyDb);
