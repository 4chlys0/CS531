/*

George Mason University
CS 531: Fundamentals of Systems Programming

Homework 1

This program prompts the user for ten unique character strings to be entered from the 
keyboard. The program sorts this series of ten character strings (based on ascii value, 
and reprints all ten strings in ascending OR descending order based on user specification. 
The program then prints and labels the character string with the lowest ascii value and 
that with the highest ascii value. 

The program is invoked with command line arguments -a to specify printing in ascending 
order or -d to specify printing in descending order. Specifying a -h argument prints the
help for the command.
	
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define NUMLINES 10
#define MAXCHARS 102 //captures null terminator added by fgets() and line feed or carriage return  

int sort(char one[], char two[]); 
int inputExists(char *input_value, char **storage);
void printData(char **storage, int asc_flag);
void getInput();
void sortArray(char **storage, int asc_flag);

int main (int argc, char *argv[])
{     
  
  int command_line_options;	   
  int asc_flag = 1;	  // Flag for setting ascending order (1) or descending order (0).
	
  opterr = 0;  // Setting this prevents error messages to be passed to stderr
 
  // Checks for user not including command line arguments
  if (argc == 1) 
  {
  	printf ("Missing arguments. Please use -h for command usage.\n");			  
	exit (1);
  }

  // Parses the command line for arguments
 while ((command_line_options = getopt (argc, argv, "adh")) != -1)
    switch (command_line_options)
	{
		case 'a':           // Ascending order argument option
			asc_flag = 1;
		    break;		
		case 'd':           // Descending order argument option
			asc_flag = 0;
			break;			
		case 'h':           // Help argument option
			printf ("This command takes as input %d strings and prints them in "
					"ascending or descending order according to rank. Please use -a or -d "
					"to specify ascending or descending order, respectively.\n", NUMLINES);		
			exit (1);		
		case '?':          // All other argument cases
			fprintf(stderr, "%s: option '-%c' is invalid. Please use -a or -d to specify"
						" ascending or descending order sorting and try again.\n",
					argv[0], optopt);		
		default:
			exit (1);
	}		
		

  // Checks	any remaining flags or improperly formed flags at the command line & rejects 	
 if (optind < argc)
 {
   printf ("Please only use -a or -d to specify ascending or descending order.\n");  
   exit (1);
 }
 
 getInput(asc_flag);

 return 0;
}
 
 /*
  Capture user input and save it to each element in the array.
  Using fgets() allows us to capture user formatted data and test the size of the input;
  size is based on the value of the array, in this case 102. This accounts for the
  '0\' that is added to the end of the string by fgets() and the carriage return or 
  line feed that is being captured. 
 */
void getInput(int asc_flag)
{
 printf("Enter 10 string up to 100 characters.\n");
 char *storage[NUMLINES];
 char input[MAXCHARS];
// int i,j;    
 for (int i = 0; i <= NUMLINES - 1; i++)
 {
     printf("Enter string # %d: ", i+1);
     fgets(input, MAXCHARS, stdin);
     storage[i] = malloc(strlen(input));       

     if(inputExists(input, storage)) 
	 {
         printf("You previously used this string as input. Please try again.\n");
         i--;
     } else
     
         strcpy(storage[i], input);
 }
 
 sortArray(storage, asc_flag); 
}

/* Compares all the values in storage to the input string and returns 0 or 1 to indicate
    whether the passed input exists in the storage array of pointers.
*/
int inputExists(char *input_value, char ** storage)
{   
    while( **storage) {
        if (strcmp(input_value, *storage) == 0)
            return 1;     
        else
            storage++;
    }
    return 0;
}

/*
 From the getInput(); we pass the storage array of pointer to the sortArray(). Here,
 we use a nested for loop, to sort the data in ascending order by default. Lastly, 
 we call the printData() by passing the sorted array to printData() along with the
 command line argument to print in ascending or descending order.
*/
void sortArray(char **storage, int asc_flag)
{

 //Sort each element of the two dimensional array
 for (int i = 9; i > 0; i--)
 {
	for( int j = 0; j < i; j++)
	{
		if (strcmp(storage[j], storage[j+1])>0)
		{
			char* temp = storage[j+1];
			storage[j+1] = storage[j];
			storage[j] = temp;
 		}
	}
 }
  printData(storage, asc_flag);
}
 
/*Based on the value of asc_flag, this function displays the sorted data
   in the storage[] of pointers and prints the highest and lowest ascii values
*/
void printData(char **storage, int asc_flag)
{   
	
	if (asc_flag == 1)
	{
  	  printf("\nYour strings printed in ascending order:\n");
  	  for(int i = 0; i <= NUMLINES - 1; i++)
  	  {
   	    printf("You Entered: %s\n", storage[i]);
  	  }
 	}
 	else
 	{
  	  printf("\nYour strings printed in descending order:\n");
  	  for (int i = NUMLINES -1; i >= 0; i--)
  	  {
   	    printf("You Entered: %s\n", storage[i]);
  	  }
 	}
 	  printf("String with the lowest ascii value: %s", storage[0]);
	  printf("String with the highest ascii value: %s\n", storage[9]);

}
