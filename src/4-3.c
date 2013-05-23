
#include "common.h"
#define MAXSTKSIZE 1000

#include "stack.h"

const char * USAGE = "Write a calculator program.";

void impl( );

int calc_op(char op,int lhs,int rhs);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
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

	stk_t * k = stk_new();	

	char cur;
	int lhs;
	int rhs;

	int total = 0;

	while( (cur = fgetc(stdin)) != EOF )
	{
		if(isdigit(cur))
		{
			stk_push(k, cur - '0');
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
	stk_free(k);
}

