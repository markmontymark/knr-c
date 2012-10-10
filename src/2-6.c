
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdarg.h>
#include "sys/types.h"
#include "common.h"

const char * USAGE = "Write setbits(int x,va_args....) that sets each bit flag pass in a varargs style";

const int BIT_A = 1 << 0;
const int BIT_B = 1 << 1;
const int BIT_C = 1 << 2;
const int BIT_D = 1 << 3;

/*
struct flags
{
	uint64_t flags;
};

typedef struct flags flags_t;
#define flags_s sizeof(flags_t)
*/



void impl( );
int setbits(int x, int n, ...);

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
	unsigned int flags = 0;
	//printf("flags = 0, %d\n",flags);

	flags = setbits(flags, 1, BIT_A);
	printf("bit a set, %d\n",flags);
	flags = 0;

	flags = setbits(flags, 1, BIT_B);
	printf("bit b set, %d\n",flags);
	flags = 0;

	flags = setbits(flags, 1, BIT_C);
	printf("bit c set, %d\n",flags);
	flags = 0;

	flags = setbits(flags, 1, BIT_D);
	printf("bit d set, %d\n",flags);
	flags = 0;

	flags = setbits(flags, 2, BIT_A, BIT_B);
	printf("bit a and b set, %d\n",flags);
	flags = 0;

	flags = setbits(flags, 2, BIT_A, BIT_C);
	printf("bit a and c set, %d\n",flags);
	flags = 0;

	flags = setbits(flags, 2, BIT_A, BIT_D);
	printf("bit a and d set, %d\n",flags);
	flags = 0;

	flags = setbits(flags, 3, BIT_A, BIT_B, BIT_C);
	printf("bit a, b, c set, %d\n",flags);
	flags = 0;

}

int setbits(int x, int n, ...)
{
	va_list ap;
	unsigned int d;

	va_start(ap, n);
	for(int i = 0; i < n; i++)
	{
		d = va_arg(ap, unsigned int);
		x |= d;
	}
	va_end(ap);
	return x;
}

/*
int flags(flags_t * flags,uint64_t val)
{
	setbits(flags,1,val);
}

int flags_has(flags_t &flags,uint64_t val)
{
	setbits(flags,1,val);
	return flags.flag | val;
}
*/
