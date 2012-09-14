
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "common.h"

const char * USAGE = "Write a program that checks for balance with parentheses, brackets, braces";

void impl( char * progname, int argc, char ** argv );
void checkForBalancedParensBracketsBraces( char * filename );

struct char_stack
{
	char c;
	struct char_stack * next;
};

void char_stack_push( struct char_stack *cs,char c)
{
}

char char_stack_pop( struct char_stack *cs)
{
}

int char_stack_is_empty( struct char_stack *cs)
{
	return cs->next == NULL;
}

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl(progname,argc,argv);
	return 0;
}

void impl( char * progname, int argc, char ** argv )
{
	for( int i = 1; i < 	argc ; i++ )
		checkForBalancedParensBracketsBraces( argv[i] );
}

void checkForBalancedParensBracketsBraces( char * filename )
{
	FILE * fp = fopen(filename,"rb");
	if( !fp )
	{
		fprintf(stderr,"Error opening file %s, %s\n",filename,strerror(errno));
		return;
	}

	int state = 0; 
		// 0   outside of string literal
		// 1   inside string literal (see literalStart for which char started the string literal
		// 2   
		// 3   
	int MAX_CHARS = 1024;
	int nCharsRead;
	char buf[MAX_CHARS];
	char * charsRead;
	char lastChar;
	char curChar;

	int lineno = 1;
	int paren_balance = 0;
	int brace_balance = 0;
	int brack_balance = 0;

	int in_paren = 0;
	int in_brace = 0;
	int in_brack = 0;
	
	while( fread(buf,1,MAX_CHARS,fp) )
	{
		int i = 0;
		while( buf[i] != '\0')
		{
			curChar = buf[i];
			if(curChar == '\n')
				lineno++;
			i++;
			switch(curChar)
			{
				case '(':
					paren_balance ++;
					in_paren = 1;
					break;
				case ')':
					paren_balance --;
					if(paren_balance < 0)
						printf("parens out of balance at line %d\n",lineno);
					if(paren_balance == 0)
						in_paren = 0;
					break;

				case '[':
					brace_balance ++;
					in_brace = 1;
					break;
				case ']':
					brace_balance --;
					if(brace_balance < 0)
						printf("braces out of balance at line %d\n",lineno);
					if(brace_balance == 0)
						in_brace = 0;
					break;

				case '{':
					brack_balance ++;
					in_brack = 1;
					break;
				case '}':
					brack_balance --;
					if(brack_balance < 0)
						printf("brackets out of balance at line %d\n",lineno);
					if(brack_balance == 0)
						in_brack = 0;
					break;

			}
		}
	}

	if(paren_balance != 0)
		printf("parens out of balance at line %d\n",lineno);
	if(brace_balance != 0)
		printf("braces out of balance at line %d\n",lineno);
	if(brack_balance != 0)
		printf("brackets out of balance at line %d\n",lineno);
}


