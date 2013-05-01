
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Rewrite calloc(n, size) using malloc";

void * mycalloc(size_t nmembers, size_t sz);

typedef struct test test_t;
struct test 
{
	int id;
	char * name;
};
#define test_sz sizeof(test_t)

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	test_t * tests;
	tests = mycalloc(10,test_sz);
	int i = 10;
	while( --i )
	{
		tests->id = i;
		tests->name = "asdf";
		printf("test ptr  %p\n",tests);
		printf("test id   %d\n",tests->id);
		printf("test name %s\n",tests->name);
		tests++;
	}
	return 0;
}

void * mycalloc(size_t nmembers, size_t sz)
{
	if( nmembers == 0 || sz == 0)
		return NULL;
	
	size_t area = nmembers * sz;
	return memset( malloc(area),0,area);
}
