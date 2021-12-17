#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/timeb.h>

int main()
{
	int status;
	pid_t fork_1, fork_2;
	if (fork_1 = fork() == 0)
	{
		printf("Fork: %d\n", getpid());
		printf("Parent: %d\n", getppid());
	}
	else 
	{
		if (fork_2 = fork() == 0)
		{
			printf("Fork: %d\n", getpid());
			printf("Parent: %d\n", getppid());
		}

		else
		{
		    system("ps -x");
			waitpid(fork_1, &status, 0);
			waitpid(fork_2, &status, 0);
			printf("Main process: %d\n", getpid());
		}
	}
    struct timeb sys_time;
	struct tm *ltime;
	ftime(&sys_time);
	ltime = localtime(&sys_time.time);
	printf("%d : %d : %d : %d\n", ltime->tm_hour, ltime->tm_min, ltime->tm_sec, sys_time.millitm);
	return 0;
}