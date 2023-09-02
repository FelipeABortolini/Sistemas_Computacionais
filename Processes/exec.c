#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>


int main( void ) {
	char *argv[4] = {".", "-name", "*.c", NULL};

	int pid = fork();

	if ( pid == 0 ) {
		execvp( "find", argv );
	}

	/* Put the parent to sleep for 2 seconds--let the child finished executing */
	wait(NULL);

	printf("Finished executing the parent process\n"
	        " - the child won't get here--you will only see this once\n");

	return 0;
}
