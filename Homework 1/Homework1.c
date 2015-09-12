#include<stdio.h>
#include<string.h>

int main (int argc, char *argv[])
{
 printf("Enter 10 strings from 1 to 100 characters.\n");

 char input[11][102]; //double array to store 10 strings with max length of 100 characters
 //unsure why we needed 102 here to store 100 characters...any ideas?
 
 int i; 
 //loop control variable; can be initialized in the for loop with "gcc -std=c99 homeWork1.c -o homeWork1"
 //i.e., for (int i =0; i <= 9; i++); otherwise user format below
 for (i = 0; i <= 9; i++) //only ask for 10 strings
 {
  printf("Enter a string: ");
  fgets(input[i], sizeof(input[i]),stdin); 
  /*
   Capture user input and save it to each element in the array
   Using fgets() allows us to capture user formatted data and test the size of the input;
   size is based on the value of the array, in this case 102
  */
 }

 for (i = 0; i <= 9; i++)
 {
  //print out each of the elements in the double array
  printf("You entered: %s\n", input[i]);
 }
 return 0;
}
