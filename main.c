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

void execProc(struct Entry *historyDb, char *choice) {
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
    //puts the string from old buffer to new array
    for (a = 1; a <= i; a++){
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

//this function will run a chosen executable in the background
void run_back(struct Entry *historyDb, char *execute) {
  pid_t pid, pid2;

  //if parent, wait to prevent a zombie process
  pid = fork();
  if (pid > 0) {
    wait(NULL);
  }
  else {

    //exit the middle process to create an orphan
    pid2 = fork();
    if (pid2 > 0) {
      exit(0);
    }

    //run in background
    else {
      execProc(historyDb, execute);
      exit(0);
    }
  }
}

//this function will run a chosen executable in the foreground
void run_front(struct Entry *historyDb, char *execute) {
  pid_t pid;

  //if parent, wait to prevent zombie process
  pid = fork();
  if (pid > 0) {
    wait(NULL);
  }

  //run in foreground
  else {
    execProc(historyDb, execute);
    exit(0);
  }
}

//this function will create a pipe between two commands and run
void piper(struct Entry *historyDb, char *command1, char *command2) {
  char *tok;
  char *args1[5], *args2[5];
  int fd[2];
  int i, j;
  pid_t pidP;

  //store all the arguments for the first command into an array
  tok = strtok(command1, " \n");
  while (tok != NULL) {
    args1[i++] = tok;
    tok = strtok(NULL, " \n");
  }

  //store the arguments for the second command in an array
  tok = strtok(command2, " \n");
  while (tok != NULL) {
    args2[j++] = tok;
    tok = strtok(NULL, " \n");
  }

  //create the pipe and fork
  if (pipe(fd) != 0) {
    printf("failed to create pipe!\n") ;
    exit(1);
  }
  if ((pidP = fork()) == -1 ){
    printf("Failed to fork!\n");
    exit(1);
  }

  //parent case, replace stdin with read of pipe, and close writing to pipe
  if (pidP != 0) {
    dup2(fd[0], 0);
    close(fd[1]);
    execvp(args2[0], args2);
    exit(0);
  }
  //child case, replace stdout with write of pipe, and close read
  else {
    dup2(fd[1], 1);
    close(fd[0]);
    execvp(args1[0], args1);
    exit(0);
  }
  
}


int main(void){
  char input[50], input_2[50], input_3[50], choice[50], copy[50], command1[50], command2[50];
  char *token;
  int miss = 0;
  int pos, found = 1;
  //This is the struct that holds the env variables
  struct Block en_var[10] = { {"CC", "gcc"}, {"EDITOR", "vim"}, {"HOME", "home"}, {"OLDPWD", "old"}, {"HOST", "host"}, {"PATH", "current"}, {"PWD", "homeDict"}, {"SHELL", "Project"}, {"HISTSIZE", "5"}, {"USER", "user"}};

  //This is the struct that holds the history of user input. HISTSIZE is defined in the "history.h" file
  struct Entry historyDb[HISTSIZE];

  //Loops until exit or quit is received
  while ((strcmp(choice, "exit\n") != 0) || (strcmp(choice, "quit\n") != 0)){
    printf("%s@%s:%s>> ", en_var[9].value, en_var[4].value, en_var[6].value);
    //Gets the users first choice
    fgets(choice, 50, stdin);
    //stores the input to the history struct
    add_history(choice, historyDb);
    
    if(strcmp(choice, "export\n") == 0){
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
    else if (strcmp(choice, "env\n") == 0){
	//Prints all the variables
      printEnv(en_var);
    }
    else if (strcmp(choice, "history\n") == 0){
      //prints the history of user inputs
      print_history(historyDb);
    }
    else if(strcmp(choice, "exit\n") == 0){
      break;
    }
    else if(strcmp(choice, "quit\n") == 0){
      break;
    }

    //for piping two commands
    else if (strstr(choice, "|") != NULL) {

      //seperate the 2 grep commands and save them
      token = strtok(choice, "\n|");
      strcpy(command1, token);
      token = strtok(NULL, "\n|");
      strcpy(command2, token);

      //we want to run the pipe in a child process to continue the loop
      pid_t pid;
      pid = fork();
      if (pid == 0) {
	piper(historyDb, command1, command2);
      }
      //parent case, wait for the child process to finish before continuing
      else {
	wait(NULL);
      }
    }

    //check for the ! to look through the history
    else if (strstr(choice, "!") != NULL) {
      token = strtok(choice, "!");
      
      //loop backwards through history to get the most recent commands
      for (int j = HISTSIZE - 1; j >= 0; j--) {
	if (strcmp(token, historyDb[j].command) == 0) {
	  
	  //look for the & to run the executable in the background
	  if (strstr(token, "&") != NULL) {

	    //run in background
	    token = strtok(choice, " !&\n");
	    run_back(historyDb, token);
	  }
	  else {
	    token = strtok(choice, " \n!");
	    run_front(historyDb, token);
	  }
	}
	else {
	  miss += 1;
	}
      }
      if (miss == HISTSIZE) {
	printf("Executable not found in recent history\n");
      }
    
    }

    //run the executable in the background if it detects &
    else if (strstr(choice, "./") && strstr(choice, "&")){
      
      token = strtok(choice, " &\n");
      run_back(historyDb, token);
    }
    //check if the choice is an executable
    else if (strstr(choice, "./")!= NULL || (strstr(choice, "./") == NULL)){
      
      token = strtok(choice, " \n");
      run_front(historyDb, token);
    }
  }

  return 0;
}
