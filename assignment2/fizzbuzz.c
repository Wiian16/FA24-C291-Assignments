#include <stdio.h>

/*
 * This program will take in an input from stdin, which must be an integer.
 * The program will then start a loop counting up from zero. When it 
 * encounters a number divisible by 3, 'fizz' will be printed to stdout.
 * When it encounters a number divisible by 5, it will print 'buzz'. When
 * a number divisible by both 3 and 5, it will print 'fizzbuzz'. When none 
 * of these conditions are met, only the number will be printed. 
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
      printf("fizz");
    }
    if(index % 5 == 0){
      printf("buzz");
    }
    if(index % 3 != 0 && index % 5 != 0){
      printf("%d", index);
    }
    printf("\n");

    index++;
  }
}
