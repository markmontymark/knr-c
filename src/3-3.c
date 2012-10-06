
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write an str2 = expand(str1) to expand shorthand notations of a-z, 0-9";

void impl( );
char * expand(char * from);
int test_expand(char * from,char * expected);

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
	test_expand("This is a-z range","This is abcdefghijklmnopqrstuvwxyz range");
	test_expand("This is 0-9 range","This is 0123456789 range");
	test_expand("This is a-z0-9 range","This is abcdefghijklmnopqrstuvwxyz0123456789 range");
	test_expand("This is 0-9a-z range","This is 0123456789abcdefghijklmnopqrstuvwxyz range");
	test_expand("0-9a-z","0123456789abcdefghijklmnopqrstuvwxyz");
	test_expand("0-3-5","0123-5");
	test_expand("0123-5","012345");
	test_expand("0-z","0-z");
	test_expand("A-z","A-z");
	test_expand("a-Z","a-Z");
}

int test_expand(char * from,char * expected)
{
	if(from == NULL)
		return 0;
	if(expected == NULL)
		return -1;
	char * to = expand(from);
	if(to == NULL)
		return 1;
	int isExpected = strcmp(to,expected) == 0;
	printf("%s: test: %s, result: %s, expected: %s\n",isExpected?"passed":"failed",from,to,expected);
	free(to);
	return isExpected;
}

char * expand(char * from)
{
	char startChar;
	char endChar;
	
	char curChar;
	char prevChar = -1;
	char prevprevChar = -1;

	int curIsAlpha;

	size_t len = strlen(from)+1;
	char * to = malloc(len);
	char * toStart = to;
	int topos = 0;
	while( (curChar = *from) )
	{
		if(prevprevChar == -1)
		{
			prevprevChar = curChar;
			*to = curChar;
			to++;
			topos++;
		}
		else if(prevChar == -1)
		{
			prevChar = curChar;
			*to = curChar;
			to++;
			topos++;
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
				to--;
				topos--;
				int growBy = (int)curChar - (int)prevprevChar;
				char * tmp = realloc(toStart,len + growBy);
				if(tmp == NULL)
				{
					free(toStart);
					return NULL;
				}
				to = toStart = tmp;
				to += topos;
				len += growBy;
				for(int i = prevprevChar+1; i <= (int)curChar; i++,to++,topos++)
					*to = (char)i;
			}

			// otherwise, append to *to and rest chars
			else
			{
				*to = curChar;
				to++;
				topos++;
				prevprevChar = prevChar;
				prevChar = curChar;
			}
		}
		*from++;	
	}
	*to = '\0';
	return toStart;
}
