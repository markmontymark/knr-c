
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"
#include "hashtable.h"
#include "arraylist_str.h"

const char * USAGE = "Write a function, undef that removes entries from lookup table";

int max_word_count;
arraylist_str_t * max_words;

void parse_words(hash_table_t * ,char ** line, int lineno);
int is_word(char * str);
void impl( char * filename );
void print_hash_table_element( void * , void * );
void delete_most_common_words( hash_table_t *, arraylist_str_t *);
void get_most_common_words( void * , void * );
void find_most_common_words(void * key, void * val );
void reset_most_common_words( );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	if(argc > 1)
		for( int i = 1 ; i < argc; i++)
			impl(argv[i]);
	return 0;
}



void impl( char * filename)
{
	FILE * f = fopen(filename,"rb");
	char * line[0];
	hash_table_t * doc = hash_table_new(MODE_COPY);	
	int lineno = 0;
	while( read_line(line,1024,f) != -1)
	{
		lineno++;
		parse_words(doc,line,lineno);
	}
	printf("Original list of words\n");
	hash_table_iterate(doc,print_hash_table_element);
	reset_most_common_words();
	hash_table_iterate(doc,find_most_common_words);
	hash_table_iterate(doc,get_most_common_words);

		
	printf("Most popular word(s) found\n");
	int sz = arraylist_str_size(max_words);
	for (int i = 0; i < sz; i++)
		printf("%s\n", arraylist_str_get( max_words, i ) );

	delete_most_common_words( doc, max_words);

	printf("List of words after removing most popular word(s)\n");
	hash_table_iterate(doc,print_hash_table_element);
	hash_table_delete(doc);
}

void reset_most_common_words()
{
	max_word_count = 0;
	if(max_words != NULL)
		arraylist_str_free( max_words );
	max_words = arraylist_str_new();
}


void parse_words(hash_table_t * doc,char ** line, int lineno)
{
	char * delim = " ";
	char * result = NULL;
	strtok( * line, delim);
	result = strtok( *line, delim );
	while( result != NULL ) 
	{
		if( ! is_word(result))
		{
			result = strtok( NULL, delim );
			continue;
		}
		if(hash_table_has_key(doc,result,strlen(result)+1))
		{
			int * val = hash_table_lookup(doc,result,strlen(result)+1);
			(*val)++;
		}
		else
		{
			int val = 1;
			hash_table_add(doc,result,strlen(result)+1,&val,sizeof(val));
		}
		result = strtok( NULL, delim );
	}
}

int is_word(char * str)
{
	while( *str )
	{
		if(! isalpha(*str))
			return 0;
		str++;
	}
	return 1;
}

void find_most_common_words(void * key, void * val )
{
	if( *(int*)val > max_word_count)
		max_word_count = * (int*)val;
}
void get_most_common_words( void * key, void * val )
{	
	if( *(int*)val == max_word_count )
		arraylist_str_add( max_words, (char *) key);
}

void delete_most_common_words( hash_table_t * words, arraylist_str_t * max_words)
{
	int sz = arraylist_str_size(max_words);
	char * word;
	int word_len;
	for (int i = 0; i < sz; i++)
	{
		word = arraylist_str_get( max_words, i );
		word_len = strlen ( word );
		printf("should delete %s\n", word);
		hash_table_remove( words, word, word_len + 1 );
	}
	
}

void print_hash_table_element( void * key, void * val )
{	
	printf("key: %s, val: %d\n", (char *)key, *((int*)val) );
}
