#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define NUMLINES 10
#define MAXCHARS 102

int main (int argc, char *argv[])
{

                  
/*      
 	  This section parses the command line to obtain the ascending and descending order
	  and to ensure that the user has inputted one command line parameter 
 */
  
  int command_line_options;	   
  int asc_flag = 1;		   // Flag for setting ascending order or descending order
                           // If set to 1, it means ascending; Set to 0, it means descending
                           
  
  opterr = 0;			   // This flag prevents error messages to be passed to stderr
  
  
  // This checks for user not putting any flags at the command line 
  if (argc == 1) {
  	printf ("Missing arguments. Please use -h for command usage.\n");			  
	exit (1);
  }
  
  // This parses the command line for the sort order flag and invokes the help command
  
  while ((command_line_options = getopt (argc, argv, "adh")) != -1)
	switch (command_line_options)
		{
		case 'a':				  // Ascending order case
			asc_flag = 1;
		    break;
		
		case 'd':				 // Descending order case
			asc_flag = 0;
			break;
			
		case 'h':				 // Help with command
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
		
		// After processing the options, this checks to see if there are other remaining 
		// flags at the command line for which there are no use case. This also validates 
		// the strict use of '-' before the flag option.
		if (optind < argc){
   			printf ("Please only use -a or -d to specify ascending or descending order.\n");  
    		exit (1);
	}	
				   
	if(asc_flag) 
		printf("Sorted order will be ASCENDING\n"); 
	else printf("Sorted order will be DESCENDING\n") ; 

  /*
   Capture user input and save it to each element in the array
   Using fgets() allows us to capture user formatted data and test the size of the input;
   size is based on the value of the array, in this case 102
  */


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

//print out each of the elements in the double array 
 for (i = 0; i <= NUMLINES - 1; i++)
 {
  printf("You Entered [%d]: %s\n", i, storage[i]);
 }
 return 0;
 
 
 /* TODO
 
    int isUnique(input, storage)
    
    int sort()
    
    sorted output
    
    makefile
    
    */

}
