#include "arraylist_str.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"

static const size_t arraylist_str_s  = sizeof(arraylist_str_t);

arraylist_str_t * arraylist_str_new() 
{
	arraylist_str_t * list = malloc(arraylist_str_s);
	if(list == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in arralist_str_new: %s\n", (unsigned long)arraylist_str_s, strerror(errno) );
		return NULL;	
	}	
	list->size = 0;
	list->data = NULL;
	return list;
}

int arraylist_str_size(arraylist_str_t * list)
{
	return list->size;
}

void arraylist_str_swap(arraylist_str_t * list, int indexTo, int indexFrom) 
{
	if( list == NULL )
		return;
	char * tmpTo = arraylist_str_get(list, indexTo );
	arraylist_str_set(list, indexTo, arraylist_str_get(list, indexFrom) );
	arraylist_str_set(list, indexFrom, tmpTo );
}

void arraylist_str_set(arraylist_str_t * list, int index, char * value) 
{
	if(list == NULL)
		return;
	list->data[index] = value;
}

void arraylist_str_add(arraylist_str_t * list, char * value) 
{
  int size = arraylist_str_size(list);
  char ** new_data;

  new_data = realloc(list->data, (size + 1) * sizeof new_data[0]);
  // Copying values should be put here ...
  if (new_data)
  {
      new_data[size] = value;
      list->data = new_data;
      ++list->size;
  }
}

char * arraylist_str_get(arraylist_str_t * list, int index) 
{
	if(index < arraylist_str_size(list))
		return list->data[index];
	return NULL;
}

int arraylist_str_indexof(arraylist_str_t * list, char * value) 
{
	int sz = arraylist_str_size( list );
	for(int i = 0; i != sz; i++ ) 
		if(strcmp(list->data[i], value) == 0) 
			return i;
	return -1;
}

void arraylist_str_free(arraylist_str_t * list)
{
	if(list == NULL)
		return;
	free(list->data);
	free(list);
}
