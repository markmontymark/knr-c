
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Rewrite malloc and add bounds checking";

typedef struct test test_t;
struct test {
	int id;
	char * name;
};
#define test_s sizeof(test_t)

void * malloc_w_bounds_check( size_t sz );
void impl( );


int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
	void * tA = malloc_w_bounds_check( test_s );
	printf("got tA %p\n", tA);
}

void * malloc_w_bounds_check( size_t sz )
{
	if( sz == 0 )
		return NULL;
	void * retval = malloc(sz);
	void * test = retval;
	size_t actualSize = 0;
	while( test++ ) 
		;
	if( test == (sz+1) )
		return retval;
	if( retval != NULL )
		free(retval);
	return NULL;	
}
