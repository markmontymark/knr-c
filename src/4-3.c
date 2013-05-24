
#include "common.h"

#include "stack.h"
#include <math.h>


const char * USAGE = "Write a calculator program.";
#define MAXDIGITS 10

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
	int val;

	int total = 0;

	while( (cur = fgetc(stdin)) != EOF )
	{
		if(isdigit(cur))
		{
			int digits[MAXDIGITS];
			int n_digits = 0;
			digits[ n_digits++ ] = cur - '0';
			while( (cur = fgetc(stdin)) != EOF && isdigit(cur) && n_digits < MAXDIGITS)
				digits[ n_digits++ ] = cur - '0';
			int val =  0;
			for(int i =  0, j = n_digits - 1; i < n_digits; i ++, j-- )
				val += digits[i] * pow(10, j);
			stk_push(k, val);
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

