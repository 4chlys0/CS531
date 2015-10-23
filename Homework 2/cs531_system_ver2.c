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
#include <fcntl.h>


int main (void)
{
     // cs531_system("ls -la");
     // cs531_system("ps aux | more");
     // cs531_system("uname -a &");
        cs531_system("for i in `seq 100`; do echo Test $i; sleep 1; done;");
     // cs531_system("cat test.log");
     // cs531_system("ping -c50 8.8.8.8");
     // cs531_system(NULL);
     // cs531_system("./a_madeup_command");
}

int cs531_system(const char *comm)
{
    pid_t child;
    int  statusOfChild, fd;
    
 // Set-up sigaction handler to ignore CNTRL + C signal, the child process will inherit the signal handling
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    
    
  //Check to see if the sh interpreter is available
    fd = open("/bin/sh", O_RDONLY);
    if (fd < 0)
    {
        perror("Shell is not accessible!\n");
        return -1;
        
    } else {
        
        close(STDIN_FILENO);
        dup(fd);
          //    close(fd); // Possibly will need to clean-up and fd at some point

    }
    
  // Create a child process that through an exec() function handling an SH interpreter will be passed a executable argument
    if ((child = fork()) == 0)
    {

           if (execle("/bin/sh", "sh", "-c", comm, (char *)0) < 0)
            {
                printf("Invalid Command");
                exit(1);
            }
    }
    else if (child == (pid_t)(-1))
        {
            perror("Fork failed.\n");
            return(-1);
        }
    
    
    wait(&statusOfChild);  // Parent waits for child to finish
    printf("Child exited with code: %d\n", statusOfChild);
    exit(statusOfChild);
}
