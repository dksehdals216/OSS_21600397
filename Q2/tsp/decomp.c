/*
Decomp.c is the solution to Quest 2 of lab 7.
Written by Dong min An
@flaemtail@gmail.com
05/30/17

Program is designed to recieve a list of gzipped files from stdin,
then create multiple concurrent processes via fork that executes gzip
to decompress each file in the given list.
The program continues to terminate all child processes created 
in order to ensue no zombies were created.

tsp.tar is given file for demonstration.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUFFERSIZE 1000

void unix_error(char *msg)
{
        int errnum;
        errnum = errno;
        fprintf(stderr, "%s: %s\n", msg, strerror(errnum));
        exit(0);
}

pid_t Fork(void)	//Wrapper function to call error for Fork
{

        pid_t pid;

        if ((pid = fork()) < 0)
                unix_error("Fork error");
        return pid;
}

int main(int argc, char *argv[])
{
	if(argc > 1)	//Checks whether if there is at least one argument
	{
		char const* const file_n = argv[1];	//filename is first argument
		FILE* fp;
		char buffer[BUFFERSIZE];
    		fp = fopen(argv[1], "r");
		int lcounter = 0;	//loop counter that keeps track of # of childs

		while (fgets(buffer, sizeof(buffer), fp) != NULL)
		{
			printf("%s", buffer);
		}	 
        	
	}
	else	//if there is no argument, return an error
	{
		fprintf(stderr, "Argument not given\n");
	}	
}
