
#include "common.h"

const char * USAGE = "detab - replace tabs with N spaces";
const char * SHIFTWIDTH = "   ";
const int MAX_CHARS = 1024;

void impl( );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	printf("Replaces tabs with %lu spaces\n",(unsigned long)strlen(SHIFTWIDTH));
	impl();
	return 0;
}

void impl( )
{
	int nCharsRead;
	char * charsRead;
	char buf[MAX_CHARS];
	while( (charsRead = fgets(buf,MAX_CHARS,stdin)) != NULL )
	{
		while(*charsRead)
		{
			if(*charsRead == '\t')
				fputs(SHIFTWIDTH,stdout);
			else
				fputc( *charsRead, stdout);
			charsRead++;
		}
	}
}

