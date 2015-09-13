#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <unistd.h>

int main (int argc, char *argv[])
{

/*	  
REMOVE THIS COMMENT AFTER REVIEW 

STEPHAN REIMERS: "I coded and tested this, it works for the command line arguments 
parsing and setting the ascending or descending flag"
 	                   
*/

                  
/*      
 	  This section parses the command line to obtain the ascending and descending order
	  and to ensure that the user has inputted one command line parameter 
	  
										START	   
 */
  
  int command_line_options;	   
  int asc_flag = 1;		   // Flag for setting ascending order or descending order
                           // If set to 1, it means ascending; Set to 0 it means descending
                           
  
  opterr = 0;			   // This flag prevents error messages to be passed to stderr
  
  
  // This checks for user not putting any flags at the command line
  
  if (argc == 1) {
  	printf ("Missing arguments. Please use -a or -d to specify ascending or "
  	        "descending order sorting and try again.\n");			  
	return 1;
  }
  
  // This parses the command line for the right flag and sets the sort order flag, can
  // be used to expand to other options to include maybe ingesting a text file for input
  
  while ((command_line_options = getopt (argc, argv, "ad")) != -1)
	switch (command_line_options)
		{
		case 'a':				  // Ascending order case
			asc_flag = 1;
//			printf ("asc_flag = %d\n", asc_flag);
		    break;
		
		case 'd':				 // Descending order case
			asc_flag = 0;
//			printf ("asc_flag = %d\n", asc_flag);
			break;
		
		case '?':
			fprintf(stderr, "%s: option '-%c' is invalid. Please use -a or -d to specify"
						" ascending or descending order sorting and try again.\n",
					argv[0], optopt);
			break;
		
		default:
			break;
		}
				   

/*										 END	
*/



 printf("Enter 10 strings from 1 to 100 characters.\n");
 
 
 /* STEPHAN REIMERS: "I think we can probably use a char pointer array instead of a two
    dimensional array. Check out section 5.6 and 5.7 of the book.
 */
 
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
