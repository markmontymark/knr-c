
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write an expand(str1,str2) to expand shorthand notations of a-z, 0-9";

void impl( );
void expand(char * from,char *to);

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl();
	return 0;
}

void impl( )
{
	char * from = "This is a-z range";
	char * to = malloc(sizeof from);
	expand(from,to);
	printf("from: %s\nto  : %s\n",from,to);

	from = "This is 0-9 range";
	to = malloc(sizeof from);
	expand(from,to);
	printf("from: %s\nto  : %s\n",from,to);

	from = "This is a-z0-9 range";
	to = malloc(sizeof from);
	expand(from,to);
	printf("from: %s\nto  : %s\n",from,to);

	from = "This is 0-9a-z range";
	to = malloc(sizeof from);
	expand(from,to);
	printf("from: %s\nto  : %s\n",from,to);

	from = "0-9a-z";
	to = malloc(sizeof from);
	expand(from,to);
	printf("from: %s\nto  : %s\n",from,to);

	from = "0-z";
	to = malloc(sizeof from);
	expand(from,to);
	printf("from: %s\nto  : %s\n",from,to);

	from = "A-z";
	to = malloc(sizeof from);
	expand(from,to);
	printf("from: %s\nto  : %s\n",from,to);

	from = "a-Z";
	to = malloc(sizeof from);
	expand(from,to);
	printf("from: %s\nto  : %s\n",from,to);

}

void expand(char * from,char *to)
{
	char startChar;
	char endChar;
	
	char curChar;
	char prevChar = -1;
	char prevprevChar = -1;

	int curIsAlpha;
	
	while( *from )
	{
		curChar = *from;
		if(prevprevChar == -1)
		{
			prevprevChar = curChar;
			*to = curChar;
			*to++;
		}
		else if(prevChar == -1)
		{
			prevChar = curChar;
			*to = curChar;
			*to++;
		}
		else
		{
			// check for letter or digit expansion
			if(prevChar == '-' 
				&& 
				(( isalpha(prevprevChar) && isalpha(curChar) 
					&& 
						(islower(prevprevChar) && islower(curChar))
						|| (isupper(prevprevChar) && isupper(curChar))
				 )
				|| ( isdigit(prevprevChar) && isdigit(curChar)))
				&& (int)prevprevChar < (int)curChar
			){
				//printf("ready to expand %c - %c\n",prevprevChar,curChar);
				*to--;
				for(int i = prevprevChar+1; i <= (int)curChar; i++)
				{
					*to = (char)i;
					*to++;
				}
			}

			// otherwise, append to *to and rest chars
			else
			{
				*to = curChar;
				*to++;
				prevprevChar = prevChar;
				prevChar = curChar;
			}
		}
		*from++;	
	}
	*to = '\0';
}
