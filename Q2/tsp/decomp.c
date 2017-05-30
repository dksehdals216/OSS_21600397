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
#include "zlib.h"
#include <string.h>

#define BUFFERSIZE 1000
#define LENGTH 0x1000

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
void decomp(char* text)
{
	char* file_name = text;
	gzFile * file;
    	file = gzopen (file_name, "r");
    	if (! file) 
	{
        	fprintf (stderr, "gzopen of '%s' failed: %s.\n", file_name,
			strerror (errno));
            	exit (EXIT_FAILURE);
    	}
    	while (1) 
	{
        	int err;                    
	        int bytes_read;
	        unsigned char buffer[LENGTH];
       		bytes_read = gzread (file, buffer, LENGTH - 1);
        	buffer[bytes_read] = '\0';
        	printf ("%s", buffer);
        	if (bytes_read < LENGTH - 1) 
		{
            		if (gzeof (file)) 
			{
                		break;
            		}
            	else 
		{
                	const char * error_string;
                	error_string = gzerror (file, & err);
                	if (err) 
			{
                    	fprintf (stderr, "Error: %s.\n", error_string);
                    	exit (EXIT_FAILURE);
                	}
            	}
        	}
    }
    gzclose (file);

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
