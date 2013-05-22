
#include "common.h"
#define MAXSTKSIZE 1000

const char * USAGE = "Write a calculator program.";

int CURSTKSIZE;

void stk_push(char *s,int n);
char stk_pop (char *s);
void stk_dump(char *s,FILE * out);

void impl( );

int calc_op(char op,int lhs,int rhs);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

int stk_is_empty(char * s)
{
	return CURSTKSIZE < 2;
}

void stk_push(char * s,int c)
{
	if( CURSTKSIZE + 1 >= MAXSTKSIZE)
	{
		printf("[stk_push] Stack full (%d items), can't push %c\n",MAXSTKSIZE, c);
		return;
	}
	s[CURSTKSIZE] = c;
	CURSTKSIZE++;
	s[CURSTKSIZE] = '\0';
}

char stk_pop(char *s)
{
	if( stk_is_empty( s ) )
	{
		printf("[stk_pop] Stack empty, can't pop\n");
		return -1;
	}
	CURSTKSIZE--;
	char c = s[CURSTKSIZE];
	s[CURSTKSIZE] = '\0';
	return c;
}

void stk_dump(char *s,FILE * out)
{
	fprintf(out,"stk_dump:\n" );
	while( ! stk_is_empty(s) )
		fprintf(out,"%d\n", stk_pop(s) );
}

int calc_op(char op,int lhs,int rhs)
{
	int retval;
	switch(op)
	{
		case '%': retval = lhs % rhs; break;
		case '+': retval = lhs + rhs; break;
		case '-': retval = lhs - rhs; break;
		case '*': retval = lhs * rhs; break;
		case '/': retval = lhs / rhs; break;
	}
	return retval;
}


void impl( )
{
	
	char k[MAXSTKSIZE];
	CURSTKSIZE = 0;
	stk_push(k,'\0');

	char cur;
	char lhs;
	char rhs;

	int total = 0;

	while( (cur = fgetc(stdin)) != EOF )
	{
		if(isdigit(cur))
		{
			stk_push(k,cur - '0');
			continue;
		}

		switch(cur)
		{
			// handle operators
			case '%': 
			case '+': 
			case '-': 
			case '*': 
			case '/':
				//printf("got op, %c\n",cur);
				if(! stk_is_empty(k)	)
					if( (lhs = stk_pop(k)) == -1 )
					{
						printf("Bad lhs pop\n");
						return;
					}
				if(! stk_is_empty(k)	)
				{
					if( (rhs = stk_pop(k)) == -1 )
					{
						printf("Bad rhs pop\n");
						return;
					}
					fprintf(stdout, "lhs %d, rhs %d, op %c\n",lhs,rhs,cur);
					stk_push(k, calc_op(cur, lhs, rhs));
				}
				else 
				{
					stk_push(k,lhs);
					stk_push(k,cur);
				}
				break;
		}
	}
	stk_dump(k,stdout);
}

