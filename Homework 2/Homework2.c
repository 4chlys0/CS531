#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

void	sig_handler(int signo)	
{	
	if (signo == SIGINT)	
		printf("received SIGINT\n");	
}	



int main (void)
{
	cs531_system("ls -l");
}

int cs531_system(const char *comm)
{
	pid_t child, c;
	unsigned char buffer[100];
	int bytes_read, i, statusOfChild;
	
	do{
	if ((child = fork()) == 0)
	{
		int fd = open("/bin/sh", O_RDONLY);
		if (fd < 0)
		{
			printf("Shell is not accessible!\n");
			return -1;
		}
		else
		{
			close(0);
			if (dup((int) execl("/bin/sh", "sh", "-c", comm, (char *)0)) < 0)
			{
				printf("Invalid Command");
				exit(1);
			}
		}
	}
	else
	{
		if (child == (pid_t)(-1))
		{
			fprintf(stderr, "Fork failed.\n");
			return(-1);
		}
		else
		{
			wait(&statusOfChild);
			printf("Child exited with code: %d\n", statusOfChild);
		}
	}
	exit(statusOfChild);
	}
	while(signal(SIGINT,sig_handler)!=SIG_ERR)		

}
