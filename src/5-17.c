
//#include "common.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"


const char * USAGE = "Write a sort() to sort lines, allow for an n arg that sorts by field number n";

void impl( char * path );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	if(argc < 2)
		return 0;
	for(int i = 1; i < argc ; i++)
		impl(*++argv);
	return 0;
}

void impl( char * path )
{
	FILE * fp = fopen(path,"rb");
	if( !fp )
	{
		perror(path);
		return;
	}

	printf("Processing %s\n",path);
}
