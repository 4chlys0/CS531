#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define NUMLINES 10
#define MAXCHARS 102

//signature declarations
int sort(char one[], char two[]); 
int stringExists(char *input, char ** storage);
void printData(char **storage, int asc_flag);

int main (int argc, char *argv[])
{     
  /*      
   This section parses the command line to obtain the ascending and descending order
   and to ensure that the user has inputted one command line parameter  
  */
  int command_line_options;	   
  int asc_flag = 1;	 
  /*Flag for setting ascending order or descending order.
    If set to 1, it means ascending; Set to 0, it means descending
  */	
  opterr = 0;  // This flag prevents error messages to be passed to stderr
  // This checks for user not putting any flags at the command line 
  if (argc == 1) 
  {
  	printf ("Missing arguments. Please use -h for command usage.\n");			  
	exit (1);
  }
  // This parses the command line for the sort order flag and invokes the help command
 while ((command_line_options = getopt (argc, argv, "adh")) != -1)
    switch (command_line_options)
	{
		case 'a':// Ascending order case
			asc_flag = 1;
		    break;		
		case 'd': // Descending order case
			asc_flag = 0;
			break;			
		case 'h': // Help with command
			printf ("This command takes as input %d strings and sorts them in "
					"ascending or descending order according to rank. Please use -a or -d "
					"to specify ascending or descending order, respectively.\n", NUMLINES);		
			exit (1);		
		case '?':
			fprintf(stderr, "%s: option '-%c' is invalid. Please use -a or -d to specify"
						" ascending or descending order sorting and try again.\n",
					argv[0], optopt);		
		default:
			exit (1);
	}		
		/* After processing the options, this checks to see if there are other remaining 
		   flags at the command line for which there are no use case. This also validates 
		   the strict use of '-' before the flag option.
		*/
 if (optind < argc)
 {
   printf ("Please only use -a or -d to specify ascending or descending order.\n");  
   exit (1);
 }
  /*
   Capture user input and save it to each element in the array
   Using fgets() allows us to capture user formatted data and test the size of the input;
   size is based on the value of the array, in this case 102
   Added logic to check for duplicates.
  */
 printf("Enter 10 string up to 100 characters.\n");
 char *storage[NUMLINES];
 char input[MAXCHARS];
 int i,j;
    
 for (i = 0; i <= NUMLINES - 1; i++)
 {
     printf("Enter a string: ");
     fgets(input, MAXCHARS, stdin);
     storage[i] = malloc(strlen(input));       
     // Validation of Input 
     if(stringExists(input, storage)) 
	 {
         printf("You have previously used this string as input. Please try again.\n");
         i--;// Reset counter to capture the input again
     } else
         strcpy(storage[i], input);
 }
	
 //Sort each element of the double array
 for (j = 9; j > 0; j--)
 {
	for(i = 0; i < j; i++)
	{
		if (sort(storage[i], storage[i+1])>0)
		{
			char* temp = storage[i+1];
			storage[i+1] = storage[i];
			storage[i] = temp;
 		}
	}
 }
 printData(storage, asc_flag); //Call the printData() function and send the storage[] and asc_flag
 return 0;
}
/* Compares all the values in storage to the input string and returns 0 or 1 to indicate
    whether the passed input exists in the storage array of pointers.
*/
int stringExists(char *input, char ** storage)
{   
    while( **storage) {
        if (strcmp(input, *storage) == 0)
            return 1;     // input matches an existing string
        else
            storage++;
    }
    return 0;
}
int sort(char one[], char two[])
{	
	if (strcmp(one, two)>0){
		return 1;
	}
	else{
		return 0;
	}
}
void printData(char **storage, int asc_flag)
{   
 /*Based on the value of asc_flag, this function displays the sorted data
   in the storage[] of pointers and prints the highest and lowest ascii values
 */
	int i;
	if (asc_flag == 1)
	{
  	  printf("Your strings in ascending order:\n");
  	  for( i = 0; i <= NUMLINES - 1; i++)
  	  {
   	    printf("You Entered: %s\n", storage[i]);
  	  }
	  printf("String with the lowest ascii value: %s", storage[0]);
	  printf("String with the highest ascii value: %s", storage[9]);
 	}
 	else if (asc_flag == 0)
 	{
  	  printf("Your strings in descending order:\n");
  	  for ( i = NUMLINES -1; i >= 0; i--)
  	  {
   	    printf("You Entered: %s\n", storage[i]);
  	  }
	  printf("String with the lowest ascii value: %s", storage[0]);
	  printf("String with the highest ascii value: %s", storage[9]);
 	}
}
