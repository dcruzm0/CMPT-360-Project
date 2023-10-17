/*---------------------------------------------------------------------
 *
 *
 *
 --------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "dataStructures.h"
#include "history.h"

void execProc(struct Entry *historyDb, char *choice){
  char vars[50];
  int i = 0;
  int ch = getc(stdin);
  char *args[2] = {choice, NULL};
  //If the user inputs additional variables
  if (ch != '\n'){
    ungetc(ch, stdin);
    char *buffer[50];
    //Get the other variables
    scanf("%[^\n]s", vars);
    char *word = strtok(vars, " "); 
    //Puts the variables in a temporary buffer
    while(word!=NULL){
      buffer[i] = word;
      i++;
      word = strtok(NULL, " ");
    }
    //Creates the array that will be passed
    char *args[i+2];
    args[0] = choice;
    int a;
    //Puts strings from old buffer to new array
    for(a = 1; a <= i; a++){
      args[a] = buffer[a-1];
    }
    args[a+1] = NULL;
    execvp(args[0], args);
  }
  else{
    printf("\nstdin is empty\n");
    execvp(args[0], args);
  }
}

int main(void){
  char input[21], input_2[21], input_3[15], choice[10], copy[21];
  
  int pos, found = 1;
  //This is the struct that holds the env variables
  struct Block en_var[10] = { {"CC", "gcc"}, {"EDITOR", "vim"}, {"HOME", "home"}, {"OLDPWD", "old"}, {"HOST", "host"}, {"PATH", "current"}, {"PWD", "homeDict"}, {"SHELL", "Project"}, {"HISTSIZE", "5"}, {"USER", "user"}};

  //This is the struct that holds the history of user input. HISTSIZE is defined in the "history.h" file
  struct Entry historyDb[HISTSIZE];

  //Loops until exit or quit is received
  while ((strcmp(choice, "exit") != 0) || (strcmp(choice, "quit") != 0)){
    printf("%s@%s:%s>> ", en_var[9].value, en_var[4].value, en_var[6].value);
    //Gets the users first choice
    scanf("%s", choice);
    //stores the input to the history struct
    add_history(choice, historyDb);
    
    if(strcmp(choice, "export") == 0){
      //Gets which variable the user wants to change and what value
      scanf("%s", input);
      //adds this user input to the history database
      add_history(input, historyDb);
      pos = 0;
      //Get the variable
      strcpy(copy, input);
      char * token = strtok(copy, "=");
      
      strcpy(input_2, token);
	//Gets the value the user wants to change the variable to
      for(int i = 0; i != sizeof(input)/sizeof(char); i++){
	if(found == 0){
	  input_3[pos] = input[i];
	  pos++;
	}
	else{
	  copy[i] = toupper(copy[i]);
	}

	if(input[i] == '='){
	  pos = 0;
	  found = 0;
	}
      }
      found = 1;
      //Updates the env struct
      setData(copy, input_3, en_var);
    }
    else if (strcmp(choice, "env") == 0){
      //Prints all the variables
      printEnv(en_var);
    }
    else if (strcmp(choice, "history") == 0){
      //prints the history of user inputs
      print_history(historyDb);
    }
    else if(strcmp(choice, "exit") == 0){
      break;
    }
    else if(strcmp(choice, "quit") == 0){
      break;
    }
    else{
      pid_t pid = fork();
      if(pid>0){
	wait(NULL);
      }
      else{
	execProc(historyDb, choice);
	exit(0);
      }
      int c;
      while((c = getchar()) != '\n' && c != EOF);
    }
    
  }
  
  return 0;
}
