#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int stk_peek(stk_t * s, int idx)
{
	int sz;
	if(idx < 0 || ( (sz = arraylist_int_size(s->data)) < idx))
	{
		fprintf(stderr,"stk_peek out of bounds check at index %d\n",idx);
		return 0;
	}
	return arraylist_int_get( s->data, idx);
}

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

int stk_get_top(stk_t * s)
{
	int sz = s->data->size;
	if(sz < 1)
		return -1;
	return arraylist_int_get(s->data,sz-1);
}

void stk_swap(stk_t * s,int srcI, int destI)
{
	int lastIdx = arraylist_int_size( s->data ) - 1;
	if( lastIdx < 1 ) // nothing to swap
		return;
	int srcIdx = lastIdx - srcI;
	int destIdx = lastIdx - destI;
	if( srcIdx < 0 || destIdx < 0 ) // nothing to swap
		return;
	int src = arraylist_int_get(s->data,srcIdx);
	int dest = arraylist_int_get(s->data,destIdx);
	arraylist_int_set(s->data,srcIdx,dest);
	arraylist_int_set(s->data,destIdx,src);
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

void stk_print(stk_t * s,FILE * out)
{
	fprintf(out,"stk_dump:\n" );
	int sz = arraylist_int_size( s->data );
	while( --sz	 > 0 )
		fprintf(out,"%d\n", arraylist_int_get(s->data,sz) );
}

void stk_free(stk_t * s)
{
   if(s == NULL)
      return;
   if(s->data != NULL)
		arraylist_int_free(s->data);
	free(s);
}

