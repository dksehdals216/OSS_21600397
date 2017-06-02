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

#define BUFFERSIZE 80
#define FILE_S 12

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

	if(argc == 1)	//Checks whether if there is at least one argument
	{
			//filename is first argument
		FILE* fp;
		char c_buffer[BUFFERSIZE], *buffer[BUFFERSIZE];
    		fp = stdin;
		int lcounter = 0;	//loop counter that keeps track of # of childs
		int i, row, col;
		char str[80];		
		
		pid_t pids[FILE_S];		
		int n = FILE_S;
		
	
		    /* Initializing array */
    		for (row = 0; row < FILE_S; row++) 
		{
        	    	buffer[row] = "  ";
        		
		}

		/* Reading file into array */
		for (row = 0; row < FILE_S; row++) 
		{
       			if (fgets(c_buffer, BUFFERSIZE, stdin))
          			buffer[row] = strdup(c_buffer);
    		}

		/* Printing array */
    		for (row = 0; row < FILE_S; row++) 
		{
			if ((pids[row] = Fork()) < 0)
			{
				perror("Error caused by fork");
				abort();
			}
			else if (pids[row] == 0)
			{
				
            			printf("%s", buffer[row]);
				sprintf(str, "gunzip %s", buffer[row]);
			//printf("%s", str);
				system(str);
			//execlp("gunzip", "gunzip", buffer[row], NULL);
				exit(0);
			}
    		}			 
        	fclose(fp);

		//Exiting Child
		int status;
		pid_t pid;
		while( n > 0)
		{
			pid = wait(&status);
			printf("Child with PID%ld exited with status 0x%x. \n", (long)pid, status);
			--n;
		}
	}
	else	//if there is no argument, return an error
	{
		fprintf(stderr, "Argument not given\n");
	}	
}
