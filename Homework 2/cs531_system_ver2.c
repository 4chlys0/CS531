/*
 George Mason University
 CS 531: Fundamentals of Systems Programming
 Homework 2
 This program implements a customized of the Linux/Unix system() library call. Similar to the system() function, the
 new version cs531_system() function hands its argument command to the sh command interpreter.  The parent process 
 waits for the shell to finish executing the command while ignoring the SIGINT (CNTRL + C) signal. The version of this 
 function uses the open(), fork(), close(), and dup() functions and implements the sigaction signal handling 
 structure.
 
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



int main (void)
{
     // cs531_system("ls -la");
     // cs531_system("ps aux | more");
     // cs531_system("uname -a &");
        cs531_system("for i in `seq 100000`; do echo Test $i; sleep 1; done;");
     // cs531_system("cat test.log");
     // cs531_system(NULL);
     // cs531_system("TEST");
}

int cs531_system(const char *comm)
{
    pid_t child;
    int  statusOfChild;
    
    
    // Set-up sigaction handler to ignore CNTRL + C signal
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
  
    
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

      
            if (dup((int) execle("/bin/sh", "sh", "-c", comm, (char *)0)) < 0)
            {
                printf("Invalid Command");
                exit(1);
            }
    
        }
    }
    else if (child == (pid_t)(-1))
        {
            perror("Fork failed.\n");
            return(-1);
        }
    
    wait(&statusOfChild);
    printf("Child exited with code: %d\n", statusOfChild);
    exit(statusOfChild);
}
