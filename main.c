/*---------------------------------------------------------------------
 *
 *
 *
 --------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataStructures.h"

int main(void){
  int choice = 0;
  char input[21], input_2[21];
  struct Block data[50];
  printf("Welcome to the data structure.");
  while (choice != 6){
    printf("\n\n1. Add an entry\n");
    printf("2. Remove an entry\n");
    printf("3. Search an entry\n");
    printf("4. Print All\n");
    printf("5. Print entry\n");
    printf("6. Exit\n");
    printf("Please select an option: ");
    scanf("%d", &choice);
    if(choice == 1){
      printf("Please enter a key to input: ");
      scanf("%s", input);
      printf("Please enter a value to input: ");
      scanf("%s", input_2);
      setData(input, input_2, data);
    }
    else if (choice == 2){
      printf("Please enter a key to remove for: ");
      scanf("%s", input);
      removeData(input, data);
    }
    else if (choice == 3){
      printf("Please enter a key to search for: ");
      scanf("%s", input);
      searchBlock(input, data);
    }
    else if(choice == 4){
      printAll(data);
    }
    else if(choice == 5){
      printf("Please enter a key to search for: ");
      scanf("%s", input);
      printBlock(input, data);
    }
  }
  
  return 0;
}
