
// This file auto-generated on Tue Aug 21 13:50:45 2012

//#include "common.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "arraylist_str.h"


const char * USAGE = "Write a sort() to sort lines, allow for an n arg that sorts by field number n";

void impl( char * path );

void sort( char ** lines, int field );
void sort_algo_quicksort();
void sort_algo_mergesort();

void q_sort_alist_str(arraylist_str_t * items, int left, int right);
void quicksort_alist_str(arraylist_str_t * items, int array_size);

void q_sort_int(int items[], int left, int right);
void quicksort_int(int numbers[], int array_size);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	if(argc < 2)
		return 0;
	for(int i = 1; i < argc ; i++)
		impl(*++argv);
	return 0;
}

void impl( char * path )
{
	FILE * fp = fopen(path,"rb");
	if( !fp )
	{
		fprintf(stderr,"Error opening file %s, %s\n", path, strerror(errno) );
		return;
	}

	printf("Processing %s\n",path);

	int MAX_CHARS = 1024;
   char buf[MAX_CHARS];
   int nCharsRead;
   char * charsRead;
   char curChar;
	int lineno = 0;

	arraylist_str_t * lines = arraylist_str_new();
	
   while( (charsRead = fgets(buf,MAX_CHARS,fp)) != NULL )
   {
		lineno++;
      nCharsRead = strlen(charsRead);
		arraylist_str_add( lines, strdup(charsRead) );
	}

	int sz = arraylist_str_size(lines);
	printf("got %d lines\n", sz);
	for(int i = 0 ; i < sz ; i++ )
		printf("%d: %s", i, arraylist_str_get(lines,i));

	quicksort_alist_str( lines, sz);

	printf("rpt %d lines\n", sz);
	for(int i = 0 ; i < sz ; i++ )
		printf("%d: %s", i, arraylist_str_get(lines,i));

	arraylist_str_free(lines);
	if( fclose(fp) )
	{
		fprintf(stderr,"Error closing file %s, %s\n", path, strerror(errno) );
		return;
	}

}

void sort( char ** lines, int field )
{
}


void quicksort_alist_str(arraylist_str_t * items, int array_size)
{
  q_sort_alist_str(items, 0, array_size - 1);
}
 
 
void q_sort_alist_str(arraylist_str_t * items, int left, int right)
{
  char * pivot, l_hold, r_hold;
 
  l_hold = left;
  r_hold = right;
  pivot = arraylist_str_get(items,left);
  while (left < right)
  {
    while( (strcmp(arraylist_str_get(items,right),pivot) >= 0) && (left < right))
      right--;
    if (left != right)
    {
      arraylist_str_swap(items,left,right);
      left++;
    }
    while( (strcmp(arraylist_str_get(items,left),pivot) <= 0) && (left < right))
      left++;
    if (left != right)
    {
      arraylist_str_swap(items,right,left);
      right--;
    }
  }
  arraylist_str_set(items,left,pivot);
  pivot = arraylist_str_get(items,left);
  left = l_hold;
  right = r_hold;
/*
  if (left < pivot)
    q_sort_alist_str(items, left, pivot - 1 );
  if (right > pivot)
    q_sort_alist_str(items, pivot+1, right);
*/
}


void quicksort_int(int numbers[], int array_size)
{
  q_sort_int(numbers, 0, array_size - 1);
}
 
 
void q_sort_int(int numbers[], int left, int right)
{
  int pivot, l_hold, r_hold;
 
  l_hold = left;
  r_hold = right;
  pivot = numbers[left];
  while (left < right)
  {
    while ((numbers[right] >= pivot) && (left < right))
      right--;
    if (left != right)
    {
      numbers[left] = numbers[right];
      left++;
    }
    while ((numbers[left] <= pivot) && (left < right))
      left++;
    if (left != right)
    {
      numbers[right] = numbers[left];
      right--;
    }
  }
  numbers[left] = pivot;
  pivot = left;
  left = l_hold;
  right = r_hold;
  if (left < pivot)
    q_sort_int(numbers, left, pivot-1);
  if (right > pivot)
    q_sort_int(numbers, pivot+1, right);
}
