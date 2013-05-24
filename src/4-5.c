 
#include "common.h"
#include "stack.h"
#include <math.h>

#define MAXDIGITS 10
const char * USAGE = "Write a calculator program, add access to Math library functions, sin, exp and pow";


void impl( );
int calc_op(char op,int lhs,int rhs);
void calc_print_top(stk_t *, FILE *);
void calc_swap_top(stk_t *);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void calc_print_top(stk_t * s, FILE * f)
{
	if( stk_is_empty(s) )
	{
		fprintf(f,"Stack is empty, no top element\n");
		return;
	}
	fprintf(f, "Top element is %d\n", stk_get_top(s));
}

void calc_swap_top(stk_t * s)
{
	if( stk_is_empty(s) )
	{
		fprintf(stderr,"Stack is empty, can't swap top two elements\n");
		return;
	}
	stk_swap( s, 0, 1 );
	stk_print( s , stdout);
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
		case '^': retval = (int)pow(lhs,rhs); break;
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
			// unary operators
			case 'e': 
				if(! stk_is_empty(k)	)
				{
					if( (lhs = stk_pop(k)) == -1 )
					{
						printf("Bad lhs pop\n");
						return;
					}
					printf("exp of %d is %f\n", lhs, exp(lhs));
					stk_push(k, exp((double)lhs));
				}
				break;
			case 'i': 
				if(! stk_is_empty(k)	)
				{
					if( (lhs = stk_pop(k)) == -1 )
					{
						printf("Bad lhs pop\n");
						return;
					}
					printf("sin of %d is %f\n", lhs, sin(lhs));
					stk_push(k, sin((double)lhs));
				}
				break;
		
			// binary operators
			case '%': 
			case '+': 
			case '-': 
			case '*': 
			case '/':
			case '^':
				//printf("got op, %c\n",cur);
				if(! stk_is_empty(k)	)
				{
					if( (lhs = stk_pop(k)) == -1 )
					{
						printf("Bad lhs pop\n");
						return;
					}
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

			// stack operators
			case 'p': 
				calc_print_top(k,stdout); 
				break;

			case 's': 
				calc_swap_top(k); 
				break;
		}
	
	}
	stk_dump(k,stdout);
	stk_free(k);
}


