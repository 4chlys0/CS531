#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main (void)
{
 printf("Enter 10 strings from 1 to 100 characters.\n");

 char *storage[11];
 int i; 
 char input[100];
 
 for (i = 0; i <= 9; i++)
 {
  printf("Enter a string: ");
  fgets(input, sizeof(input),stdin);
  input[strlen(input)-1] = '\0';
  storage[i] = input;
 }

 for (i = 0; i <= 9; i++)
 {
  printf("You entered: %s\n", storage[i]);
 }
 return 0;
}
