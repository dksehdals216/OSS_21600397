#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFERSIZE 1000

void unix_error(char *msg)
{
        int errnum;
        errnum = errno;
        fprintf(stderr, "%s: %s\n", msg, strerror(errnum));
        exit(0);
}

pid_t Fork(void)
{

        pid_t pid;

        if ((pid = fork()) < 0)
                unix_error("Fork error");
        return pid;
}

int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		char const* const file_n = argv[1];	
		FILE* fp;
		char buffer[BUFFERSIZE];
    		fp = fopen(argv[1], "r");
		while (fgets(buffer, sizeof(buffer), fp) != NULL)
		{
			printf("%s | \n", buffer);
		}	 
        	
	}
	else
	{
		fprintf(stderr, "Argument not given\n");
	}	
}
