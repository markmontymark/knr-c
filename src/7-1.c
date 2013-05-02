  
#include <stdio.h>
#include <string.h>

const char * USAGE = "Write a program, like rcfile, that changes behavior based on name of argv[0]";

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	char * fullprogname = strdup(*argv,"/");
	char * progname = rindex(fullprogname,'/');
	if(progname != NULL)
		progname++;
	else
		progname = fullprogname;
	
	printf("%s\n",progname);
	if( strcmp("asdf",progname) == 0 )
		printf("Doing whatever %s tells me to do\n",progname);
	else if( strcmp("fdsa",progname) == 0 )
		printf("I must be %sing my mind\n",progname);
	else
		printf("wotevs\n");
	return 0;
}
