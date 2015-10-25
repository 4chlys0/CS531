/*
George Mason University
CS 531: Fundamentals of Systems Programming
Homework 2
This program attempts to recreate the C library function "int system(const char*comm)"
which executes subprocesses and commands. Run properly, this code should spawn a child
and execute the command specified within the main method.

Authors:
	Stephan Reimers
	Christopher Day
	Rijul Mandlekar
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

/*
Allows interruption and exiting when
"ctrl-c" is pressed
*/
void	sig_handler(int signo)	
{	
	if (signo == SIGINT)	
		printf("received SIGINT\n");	
}	


/*
Main method with preexisting ls command
*/
int main (void)
{
	cs531_system("ls -l");
}

/*
Attempts to spawn a shell and execute a command as well
as forking and creating a new child.
*/
int cs531_system(const char *comm)
{
	pid_t child, c;
	unsigned char buffer[100];
	int bytes_read, i, statusOfChild;
	
	do{
	if ((child = fork()) == 0) //Process with Pid 0
	{
		int fd = open("/bin/sh", O_RDONLY);
		if (fd < 0)
		{
			printf("Shell is not accessible!\n");
			return -1;
		}
		else //Sucessful shell generation
		{
			close(0);
			if (dup((int) execl("/bin/sh", "sh", "-c", comm, (char *)0)) < 0)
			{
				printf("Invalid Command");
				exit(1);
			}
		}
	}
	else //Process with new Pid
	{
		if (child == (pid_t)(-1))
		{
			fprintf(stderr, "Fork failed.\n");
			return(-1);
		}
		else//Sucessful child process generation
		{
			wait(&statusOfChild);
			printf("Child exited with code: %d\n", statusOfChild);
		}
	}
	exit(statusOfChild);
	}
	while(signal(SIGINT,sig_handler)!=SIG_ERR);		

}
