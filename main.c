/*---------------------------------------------------------------------
 *
 *
 *
 --------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructures.h"
#include "history.h"

int main(void){
  char input[21], input_2[21], input_3[15], choice[10], copy[21];
  
  int pos, found = 1;
  //This is the struct that holds the env variables
  struct Block en_var[10] = { {"CC", "gcc"}, {"EDITOR", "vim"}, {"HOME", "home"}, {"OLDPWD", "old"}, {"HOST", "host"}, {"PATH", "current"}, {"PWD", "homeDict"}, {"SHELL", "Project"}, {"HISTSIZE", "5"}, {"USER", "user"}};

  //Loops until exit or quit is received
  while ((strcmp(choice, "exit") != 0) || (strcmp(choice, "quit") != 0)){
    printf("%s@%s:%s>> ", en_var[9].value, en_var[4].value, en_var[6].value);
    //Gets the users first choice
    scanf("%s", choice);
    
    if(strcmp(choice, "export") == 0){
           //Gets which variable the user wants to change and what value
      scanf("%s", input);
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
      
    }
    else if(strcmp(choice, "exit") == 0){
      break;
    }
    else if(strcmp(choice, "quit") == 0){
      break;
    }
    
  }
  
  return 0;
}
