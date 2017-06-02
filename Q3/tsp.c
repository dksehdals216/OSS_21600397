#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int m[17][17] ;

int path[17] ;
int used[17] ;
int length = 0 ;
static int min = -1 ;

void handler(int signum) {
	if (signum == SIGINT) {
		printf("\n%d\n", min);
		exit(0) ;
	}
}
	
void _travel(int idx) {
	int i ;

	if (idx == 17) {
		if (min == -1 || min > length) {
			min = length ;
			printf("%d (", length) ;
			for (i = 0 ; i < 16 ; i++) 
				printf("%d ", path[i]) ;
			printf("%d)\n", path[16]) ;
		}
	}
	else {
		for (i = 0 ; i < 17 ; i++) {
			if (used[i] == 0) {
				path[idx] = i ;
				used[i] = 1 ;
				length += m[path[idx-1]][i] ;
				_travel(idx+1) ;
				length -= m[path[idx-1]][i] ;
				used[i] = 0 ;
			}
		}
	}
}

void travel(int start) {
	path[0] = start ;
	used[start] = 1 ;
	_travel(1) ;
	used[start] = 0 ;
}

int main() {
	int i, j, t ;

	FILE * fp = fopen("gr17.tsp", "r") ;

	signal(SIGINT, handler) ;

	for (i = 0 ; i < 17 ; i++) {
		for (j = 0 ; j < 17 ; j++) {
			fscanf(fp, "%d", &t) ;
			m[i][j] = t ;
		}
	}
	fclose(fp) ;

	pid_t pid;
	
	
	for (i = 0  ; i < 17 ; i++)
	{ 
		if ((pid = fork) < 0)
		{
			perror("Error fork");
			abort();
		}
		else if (pid == 0)
		{
			travel(i);	
		}
		
	}
	//Exiting Child
        int status;
        pid_t pid;
	int n = 17;
        while( n > 0)
        {
                pid = wait(&status);
                printf("Child with PID%ld exited with status 0x%x. \n", (long)pid, status);
                --n;
        }

}
