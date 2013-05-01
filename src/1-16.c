#include "common.h"


const char * USAGE = "Print the length of arbitrarily long input lines and all the text in line";

void impl( );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
	int bufsize = 24;
	char buf[bufsize];
	char * retval;
	int charsRead = 0;
	int totalCharsRead = 0;
	while( (retval = fgets(buf,bufsize,stdin)) != NULL )
	{
		fputs(retval,stdout);

		charsRead = strlen(retval);
		if(*(retval+charsRead-1) == '\n')
		{
			totalCharsRead += charsRead;
			printf("Length: %d\n",totalCharsRead);
			totalCharsRead = 0;
		}
		else
		{
			totalCharsRead += charsRead;
		}
	}
}

