  
#include "common.h"

const char * USAGE = "Write a calculator program, Our getch/ungetch don't handle pushing EOF back";

void impl( );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
}
