

// This file auto-generated on Tue Aug 21 13:50:45 2012

// inspired by answer
// http://stackoverflow.com/questions/5451104/how-to-get-memory-block-length-after-malloc/12571409#12571409

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"


typedef struct {
    size_t size;
} Metadata;

void * my_malloc(size_t sz) {
    size_t size_with_header = sz + sizeof(Metadata);
    void* pointer = malloc(size_with_header);

    // cast the header into a Metadata struct
    Metadata* header = (Metadata*)pointer;
    header->size = sz;
	 return header;
}

void * my_malloc_whats_needed( void * ptr)
{
    // return the address starting after the header 
    // since this is what the user needs
    return ptr + sizeof(Metadata);
}

size_t my_malloc_in_bounds( void * ptr, size_t expected )
{
	Metadata* header = (Metadata*)(ptr - sizeof(Metadata));
	return header->size == expected;
}

const char * USAGE = "Rewrite malloc and add bounds checking.";

void impl( );


int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	if(argc < 2)
		return 1;
	int last = argc - 1;
	int i = 0;
	while( i < last )
		impl( (size_t)atoi( argv[++i]));
	return 0;
}

void impl( size_t sz )
{
	Metadata * thingy = my_malloc(sz);
	char * mystring = my_malloc_whats_needed(thingy);
	printf("got allocation %p\n", thingy);
	printf("got var to use %p\n", mystring);
	printf("Size allocated is %lu? %s\n", sz, my_malloc_in_bounds(mystring,sz) ? "yes" : "no");
	free(thingy);
}

