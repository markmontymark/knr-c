#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

stk_t * stk_new()
{
	stk_t * s = malloc(stk_s);
	if(s == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in stk_new: %s\n", (unsigned long)stk_s, strerror(errno) );
		return NULL;
	}
	s->data = arraylist_int_new();
	s->idx = -1;
	return s;
}


int stk_is_empty(stk_t * s)
{
	if( s == NULL || s->data == NULL )
		return 1;
	return s->idx == -1;
}


void stk_push(stk_t * s,int n)
{
	arraylist_int_add(s->data,n);
	s->idx++;
}


int stk_pop (stk_t * s)
{
	int retval = arraylist_int_get(s->data,s->idx);
	free(s->data->data[s->idx]);
	s->data->size --;
	s->idx--;
	return retval;
}


void stk_dump(stk_t * s,FILE * out)
{
	fprintf(out,"stk_dump:\n" );
	while( ! stk_is_empty(s) )
		fprintf(out,"%d\n", stk_pop(s) );
}

void stk_free(stk_t * s)
{
   if(s == NULL)
      return;
   if(s->data != NULL)
		arraylist_int_free(s->data);
	free(s);
}

