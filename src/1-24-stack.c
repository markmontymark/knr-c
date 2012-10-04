
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "common.h"
#include "char_stack.h"

const char * USAGE = "Write a program that checks for balance with parentheses, brackets, braces";

void impl( int argc, char ** argv );
void checkForBalancedParensBracketsBraces( char * filename );

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl(argc,argv);
	return 0;
}

void impl( int argc, char ** argv )
{
	for( int i = 1; i < 	argc ; i++ )
		checkForBalancedParensBracketsBraces( argv[i] );
}

int is_balanced(struct char_stack * cs,char expectChar)
{
	return expectChar == cs->c ? 1 : 0;
}

void checkForBalancedParensBracketsBraces( char * filename )
{
	FILE * fp = fopen(filename,"rb");
	if( !fp )
	{
		fprintf(stderr,"Error opening file %s, %s\n",filename,strerror(errno));
		return;
	}

	int MAX_CHARS = 1024;
	int nCharsRead;
	char buf[MAX_CHARS];
	char * charsRead;
	char lastChar;
	char curChar;

	struct char_stack * cs = char_stack_init();

	int lineno = 1;

   while( (charsRead = fgets(buf,MAX_CHARS,fp)) != NULL )
   {
      nCharsRead = strlen(charsRead);
      for(int i = 0; i < nCharsRead; i++)
      {
         curChar = charsRead[i];
			if(curChar == '\n')
				lineno++;

			switch(curChar)
			{
				case '(':
				case '[':
				case '{':
					cs = char_stack_push( cs,curChar);
					break;

				case ')':
					if( ! is_balanced( cs, '(') )
						printf("Out of balance at line %d, found %c, expected to match %c\n",
							lineno, cs->c, '(');
					cs = char_stack_pop(cs);
					break;

				case ']':
					if( ! is_balanced( cs, '[') )
						printf("Out of balance at line %d, found %c, expected to match %c\n",
							lineno, cs->c, '[');
					cs = char_stack_pop( cs );
					break;
				case '}':
					if( ! is_balanced( cs, '{') )
						printf("Out of balance at line %d, found %c, expected to match %c\n",
							lineno, cs->c, '{');
					cs = char_stack_pop( cs );
					break;

			}
		}
	}

	if( ! char_stack_is_empty(cs) )
	{
		printf("Out of balance at end of source, dumping what's left\n");
		char_stack_dump(cs,stdout);
	}
	//char_stack_free(cs);
}


