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
	cs531_system("ls");
}

int cs531_system(const char *comm)
{
	pid_t child, c;
	unsigned char buffer[100];
	int bytes_read, i, statusOfChild;
	
	if ((child = fork()) == 0)
	{
		int fd = open("cooldark.txt", O_RDONLY);
		if (fd < 0)
		{
			printf("File could not be loaded.");
			return 1;
		}
		else
		{
			do
			{
				bytes_read = read(fd, buffer, sizeof(buffer));
				for (i = 0; i < bytes_read; i++)
					printf("%c",buffer[i]);
				printf("\n");
			}
			while (bytes_read == sizeof(buffer));
			close(fd);
		}
	}
	else
	{
		if (child == (pid_t)(-1))
		{
			fprintf(stderr, "Fork failed.\n");
			exit(1);
		}
		else
		{
			wait(&statusOfChild); //wait for child to finish reading their story
			printf("The child finished reading its story.\n Exit Code = %d\n", statusOfChild);
			execlp(comm, comm, NULL);
		}
	}
	return 0;
}
