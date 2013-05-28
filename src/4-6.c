#include "common.h"
#include "stack.h"
#include "arraylist_double.h"
#include <math.h>

#define MAXDIGITS 10
const char * USAGE = "Write a calculator program. Add commands for handling variables.   Add a variable for the most recently printed value.";


void impl( );
double calc_op(char op,double lhs,double rhs);
void calc_print_top(stk_t *, FILE *, double *);
void calc_swap_top(stk_t *);
void calc_clear(stk_t *);
void calc_set_var( arraylist_double_t * vars, int var, double value);
double calc_get_var( arraylist_double_t * vars, char var);
void calc_init_vars( arraylist_double_t * vars, int value);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}


void calc_init_vars( arraylist_double_t * vars, int value)
{
	if( vars == NULL)
		return;
	for( int i = 0; i < 26; i++ )
		arraylist_double_add(vars,0);
}


void calc_set_var( arraylist_double_t * vars, int var, double value)
{
	if( var < 0 || var > 26)
	{
		fprintf(stderr,"Error: calc_set_var can't set a var out of the range, 'a' .. 'z', got %d\n",var);
		return;
	}
	arraylist_double_set( vars, var, value);
}


double calc_get_var( arraylist_double_t * vars, char var)
{
	if(vars == NULL)
	{
		fprintf(stderr,"Error: calc_get_var can't get a var from a NULL list, got %p\n",vars);
		return 0;
	}
	if( var < 0 || var > 26)
	{
		fprintf(stderr,"Error: calc_get_var can't get a var out of the range, 'a' .. 'z', got %c\n",var);
		return 0;
	}
	return arraylist_double_get(vars,var);
}


void calc_print_top(stk_t * s, FILE * f, double * most_recently_printed)
{
	if( stk_is_empty(s) )
	{
		fprintf(f,"Stack is empty, no top element\n");
		return;
	}
	if(most_recently_printed != NULL)
		free(most_recently_printed);
	most_recently_printed = malloc(sizeof(double));
	*most_recently_printed = (double)stk_get_top(s);
	fprintf(f, "Top element is %f\n", *most_recently_printed);
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

void calc_clear(stk_t * s)
{
	if( s == NULL )
		return;
	while( ! stk_is_empty(s) )
		stk_pop(s);
}



double calc_op(char op,double lhs,double rhs)
{
	double retval;
	switch(op)
	{
		case '%': retval = (int)lhs % (int)rhs; break;
		case '+': retval = lhs + rhs; break;
		case '-': retval = lhs - rhs; break;
		case '*': retval = lhs * rhs; break;
		case '/': retval = lhs / rhs; break;
		case '^': retval = pow(lhs,rhs); break;
	}
	return retval;
}


void impl( )
{

	stk_t * k = stk_new();	

	arraylist_double_t * vars = arraylist_double_new();
	calc_init_vars( vars, 0);

	double * most_recently_printed = NULL;

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

			// exponent op
			case '<': 
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
			// sine
			case '~': 
			// cosine
			case '`': 
				if(! stk_is_empty(k)	)
				{
					if( (lhs = stk_pop(k)) == -1 )
					{
						printf("Bad lhs pop\n");
						return;
					}
					printf("%s of %d is %f\n", cur == '~' ? "sine" : "cosine", lhs, sin(lhs));
					stk_push(k, cur == '~' ? (sin((double)lhs)) : (cos((double)lhs)) );
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
			// _  = clear stack
			case '_': 
				calc_clear(k); 
				break;

			// print top stack element
			case '.': 
				calc_print_top(k,stdout,most_recently_printed); 
				break;

			// swap two top stack elements
			case '>': 
				calc_swap_top(k); 
				break;

			// push most recently printed 
			case '$': 
				stk_push(k, *most_recently_printed);
				break;

			// set a var, leave var's value on the stack
			case '=':
			{
				int mvar = stk_pop(k);
				double mval = (double)stk_pop(k);
				//printf("calc_set_var got var %d, got val %f\n",mvar,mval);
				calc_set_var( vars, mvar, mval);
				stk_push(k, mval);
				break;
			}
		
			// get a var value and leave value on the stack
			case '{':
			{
				int mvar = stk_pop(k);
				double mval = calc_get_var( vars, mvar);
				//printf("calc_get_var, var is %d, val is %f\n", mvar,mval);
				stk_push(k, mval);
				break;
			}


			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
			case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
			case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
			case 's': case 't': case 'u': case 'v': case 'w': case 'x':
			case 'y': case 'z':
				stk_push(k, cur - 'a');
				break;
		}
	
	}

	stk_dump(k,stdout);
	stk_free(k);
	if( most_recently_printed != NULL)
		free(most_recently_printed);

	arraylist_double_free(vars);
}


