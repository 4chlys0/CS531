#include<stdio.h>

int main (int argc, char *argv[])
{
 printf("Enter 10 strings up to 100 characters.\n");

 char input[11][102]; 
 int i; 

 for (i = 0; i <= 9; i++) 
 {
  printf("Enter a string: ");
  fgets(input[i], sizeof(input[i]),stdin); 
 }

 for (i = 0; i <= 9; i++)
 {
  printf("You entered: %s\n", input[i]);
 }
 return 0;
}
