#include <stdio.h>
#include <string.h>

const char * USAGE = "fold long input lines into two or more shorter lines with max length of 80 chars";
const int MAX_LINELENGTH = 80;
const int MAX_CHARS = 1024;

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);

	char * charsRead;
	char buf[MAX_CHARS];
	int nCharsRead;
	int charsPerLine = 0;
	while( (charsRead = fgets(buf,MAX_CHARS,stdin)) != NULL )
	{
		nCharsRead = strlen(charsRead);
		for(int i = 0; i < nCharsRead; i++)
		{
			if( charsRead[i] == '\n')
			{
				charsPerLine = 0;
				fputc('\n',stdout);	
			}	
			else
			{
				fputc(charsRead[i],stdout);
				charsPerLine++;
				if( charsPerLine == MAX_LINELENGTH )
				{
					charsPerLine = 0;
					fputc('\n',stdout);	
				}
			}
		}
	}
	
}

