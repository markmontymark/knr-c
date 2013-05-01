
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "common.h"
#include "sorted_tree.h"

const char * USAGE = "Write a cross-referencer that prints a list \
of all words in  a document and, for each word, a list of the line\
 numbers of occurences of each word.  Have an ignore list of words\
 like 'a', 'the, etc.";


void parse_words(ordered_tree_str_t * d,char ** line, int lineno);
int is_word(char * str);
void impl( char * filename );
void print_ordered_tree_str( ordered_tree_str_t * node );



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
	ordered_tree_str_t * doc = ordered_tree_str_new("");
	int lineno = 0;
	while( read_line(line,1024,f) != -1)
	{
		lineno++;
		parse_words(doc,line,lineno);
	}
	ordered_tree_str_traverse(doc,print_ordered_tree_str);
	ordered_tree_str_free(doc);
}

void parse_words(ordered_tree_str_t * doc,char ** line, int lineno)
{
	char * word = strtok(*line," ");
	char * delim = " ";
	char *result = NULL;
	result = strtok( *line, delim );
	while( result != NULL ) 
	{
		if(is_word(result))
			ordered_tree_str_add(doc,result);
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

void print_ordered_tree_str( ordered_tree_str_t * node )
{
	if( strcmp(node->str,""))
		printf("%s, count %d\n",node->str,node->count);
}

