#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NUMLINES 10
#define MAXCHARS 102

int main (int argc, char *arv[])
{
 printf("Enter 10 string up to 100 characters.\n");

 char *storage[NUMLINES];
 char input[MAXCHARS];
 int i;

 for (i = 0; i <= NUMLINES - 1; i++)
 {
  printf("Enter a string: ");
  fgets(input, MAXCHARS, stdin);
  storage[i] = malloc(strlen(input));
  strcpy(storage[i], input);
 }
 
 for (i = 0; i <= NUMLINES - 1; i++)
 {
  printf("You Entered [%d]: %s\n", i, storage[i]);
 }
 return 0;
}
