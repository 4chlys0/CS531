#include<stdio.h>
#include<strings.h>


DEFINE upperBound = 100;
DEFINE lowerBound = 1;


int main (parse arguments for user decisions for ascending/descending)
{
error check- validate user input includes only one choice for ascending/descending)
 
 printf("Enter 10 strings from 1 to 10 characters.\n");


 int lcv;
 char str[10]; //start off with small array
 
 for (lcv = 0; lcv <= 3; lcv++)
 {
  printf("Enter a string: "); /*ask for 10 separate strings*/
  scanf("%s", str); //send to compare() return 1 if not in list; 0 if it is
 
 error check: if (str is between 1 and 100 AND is not a SPACE)
  
 }
 while (str)
 {
  printf("You entered: %s\n", str);
 }
 return 0;
}




MakeFile
CFLAGS=-Wall -g

clean:
  rm -f Homekwork1


int Compare (char [])
{}


int sort(void)
{}