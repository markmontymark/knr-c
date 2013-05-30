
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Revise minprintf to handle more of the other facilities of printf";

void impl( );
void minprintf( char * fmt, ... );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{

	minprintf("This is an int %d\n", 10);
	minprintf("This is an double %f\n", 10.0);
	minprintf("This is a string %s\n", "10");
	minprintf("This is a literal %% followed by a char * of %s and a char %d\n","%", '%');
	minprintf("This is a long int %l\n", 1234567891011121314);
	minprintf("This is a long long int %ll\n", 1234567891011121314);

	char * s;
	minprintf("This is a pointer not initialized %p\n", s );
	s = "text";
	minprintf("This is a pointer initialized %p\n", s );
}


void minprintf( char * fmt, ... )
{
	va_list ap;
	char * p, 
		* sval,
		*nextP;
	void * pval;

	int ival;
	double dval;
	long int lval;
	long long int llval;
	
	va_start( ap, fmt );
	for( p = fmt; *p; p++ )
	{
		if( *p != '%' )
		{
			fputc(*p,stdout);
			continue;
		}
		switch( * ++p )
		{
			// orig specifiers: d f s
			case 'd':
				ival = va_arg( ap, int);
				printf("%d",ival);
				break;
			case 'f':
				dval = va_arg( ap, double);
				printf("%f",dval);
				break;
			case 's':
				for( sval = va_arg(ap,char *); *sval; sval++)
					fputc(*sval,stdout);	
				break;
			
			// new specifiers: l ll p
			case 'l':
				if( *(nextP = (p+1)) == 'l')
				{	
					* ++p;
					llval = va_arg( ap, long long int);
					printf("%lli",llval);
				}
				else
				{
					lval = va_arg( ap, long int);
					printf("%li",lval);
				}
				break;
			case 'p':
				pval = va_arg( ap, void *);
				printf("%p",pval);
				break;


			// orig default
			default:
				fputc(*p,stdout);
				break;
		}
	}
	va_end(ap);
}
