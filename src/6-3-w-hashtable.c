
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include "common.h"
#include "hashtable.h"

const char * USAGE = "Write a cross-referencer that prints a list \
of all words in  a document and, for each word, a list of the line\
 numbers of occurences of each word.  Have an ignore list of words\
 like 'a', 'the, etc.";


void parse_words(hash_table_t * ,char ** line, int lineno);
int is_word(char * str);
void impl( char * filename );
void print_hash_table_element( void * , void * );


/*
int read_line(char ** dest, int realloc_size, FILE *fp) 
{
	char *t=NULL, *p=NULL;
	int c; // character buffer 
	int len = 0; // current number of elements read and stored 
	int allocated = 0; // number of allocated bytes in p 

	p = malloc(realloc_size);
	if(p == NULL)
		return -1;

	allocated = realloc_size;

	while( 
		(c = fgetc(fp)) != EOF 
		&& c != '\n'
	)
	{
		if(len == allocated) 
		{
			t = realloc(p, allocated + realloc_size);
			if (t == NULL)
			{
				free(p);
				return -1;
			}
			p = t;
			allocated += realloc_size;
		}
		p[len++] = (char) c;
	}
	if(len == 0) 
	{
		if(c == EOF) 
		{
			free(p);
			return -1;
		} 
		else 
		{
			assert(c == '\n');
			p[0] = '\0';
			*dest = p;
			return 0;
		}
	}

	if( (len + 1) != allocated) 
	{
		t = realloc(p, len+1);
		if (t == NULL) 
		{
			if(p)
				free(p);
			return -1;
		}
		p = t;
	}

	p[len] = '\0';
	*dest = p;
	return len;
}

*/


int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
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
	hash_table_iterate(doc,print_hash_table_element);
	hash_table_delete(doc);
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

void print_hash_table_element( void * key, void * val )
{	
	printf("key: %s, val: %d\n", (char *)key, *((int*)val) );
}

