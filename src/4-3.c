
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write a calculator program, hello TI-80!!";

typedef char * stk;
void stk_init(stk s);
void stk_free(stk s);
void stk_push(stk s,char c);
char stk_pop (stk s);
void stk_dump(stk s,FILE * out);

void impl( );

int calc_op(char op,int lhs,int rhs);

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl();
	return 0;
}

void stk_init(stk s)
{
	*s = '\0';
}

void stk_free(stk s)
{
	free(s);
}

void stk_push(stk s,char c)
{
	printf("pre push %p, %c\n",s,c);
	*++s = c;
	printf("post push %p, %c\n",s,c);
}

char stk_pop(stk s)
{
	char c = *s;
	*--s;
	return c;
}

int stk_is_empty(stk s)
{
	return *s == '\0';
}

void stk_dump(stk s,FILE * out)
{
	while( ! stk_is_empty(s) )
	{
		fprintf(out,"stk_dump: %c\n", stk_pop(s) );
	}
}

int calc_op(char op,int lhs,int rhs)
{
	int retval;
	switch(op)
	{
		case '+': retval = lhs + rhs; break;
		case '-': retval = lhs - rhs; break;
		case '*': retval = lhs * rhs; break;
		case '/': retval = lhs / rhs; break;
	}
	printf("%d %c %d = %d\n",lhs,op,rhs,retval);
	return retval;
}


void impl( )
{
	
	stk k = malloc(1024 * sizeof(char));
	stk_init(k);

	char cur;
	char lhs;
	char rhs;

	int total = 0;

	while( (cur = fgetc(stdin)) != EOF )
	{
		if(isdigit(cur))
		{
			stk_push(k,cur);
			continue;
		}

		switch(cur)
		{
			// handle operators
			case '+': 
			case '-': 
			case '*': 
			case '/':
				if(! stk_is_empty(k)	)
					lhs = stk_pop(k);
				if(! stk_is_empty(k)	)
				{
					rhs = stk_pop(k);
					stk_push(k, calc_op(cur, lhs - '0' , rhs - '0' ));
				}
				else 
				{
					stk_push(k,lhs);
					stk_push(k,cur);
				}
		}
	}
	stk_dump(k,stdout);
	stk_free(k);
}

