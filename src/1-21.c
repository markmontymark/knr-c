
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "entab - replace N spaces with tabs";

const int SHIFTWIDTH_SIZE = 3;
const int MAX_CHARS = 1024;

void impl( char * progname );

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl(progname);
	return 0;
}

void impl( char * progname )
{
	int nCharsRead;
	char * charsRead;
	char buf[MAX_CHARS];
	int inSpaces = 0;
	int nSpaces = 0;
	while( (charsRead = fgets(buf,MAX_CHARS,stdin)) != NULL )
	{
		nCharsRead = strlen(charsRead);
		for(int i = 0; i < nCharsRead; i++)
		{
			if(inSpaces)
			{
				if(charsRead[i] == ' ')
				{
					nSpaces++;
					if(nSpaces == SHIFTWIDTH_SIZE)
					{
						fputc('\t',stdout);
						inSpaces = nSpaces = 0;
					}
				}
				else
				{
					fputc(charsRead[i],stdout);
					inSpaces = nSpaces = 0;
				}
			}
			else
			{
				if(charsRead[i] == ' ')
					inSpaces = nSpaces = 1;
				else fputc(charsRead[i],stdout);
				
			}
		}
	}
}

