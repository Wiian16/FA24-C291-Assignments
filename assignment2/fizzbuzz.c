#include <stdio.h>

/*
 * This is a block comment
 * I don't want to do this
 */
int main(void){
  int input;
  //read input from user
  printf("#### Input\n> ");
  scanf("%d", &input);

  int index = 0;

  printf("#### Output\n");

  while(index <= input){
    printf("> ");

    if(index == 0){
      printf("%d\n", index);
      index++;
      continue;
    }

    if(index % 3 == 0){
      printf("Fizz");
    }
    if(index % 5 == 0){
      printf("Buzz");
    }
    if(index % 3 != 0 && index % 5 != 0){
      printf("%d", index);
    }
    printf("\n");

    index++;
  }
}
