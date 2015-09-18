#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define NUMLINES 10
#define MAXCHARS 102 // Chris will check 

int sort(char one[], char two[]); 
int stringExists(char *input, char ** storage);
void printData(char **storage, int asc_flag);
void getInput();
void sortArray(char **storage, int asc_flag);

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
 int i,j;    
 for (i = 0; i <= NUMLINES - 1; i++)
 {
     printf("Enter a string: ");
     fgets(input, MAXCHARS, stdin);
     storage[i] = malloc(strlen(input));       

     if(stringExists(input, storage)) 
	 {
         printf("You have previously used this string as input. Please try again.\n");
         i--;
     } else
         strcpy(storage[i], input);
 }
 sortArray(storage, asc_flag); 
}
/* Compares all the values in storage to the input string and returns 0 or 1 to indicate
    whether the passed input exists in the storage array of pointers.
*/
int stringExists(char *input, char ** storage)
{   
    while( **storage) {
        if (strcmp(input, *storage) == 0)
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
 int i,j;
 //Sort each element of the double array
 for (i = 9; i > 0; i--)
 {
	for(j = 0; j < i; j++)
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
 	else if (asc_flag == 0)   // Chris will fix
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
