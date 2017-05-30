#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(void)
{
	return execl ("/bin/pwd", "pwd", NULL);
}	
