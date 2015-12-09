#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "strings.h"
#include "unistd.h"
#include "getopt.h"

const char * USAGE = "Add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting; for example 'a' and 'A' compare equal.";

#define MAXLINES 5000
#define MAXLEN 5000
#define ALLOCSIZE 100000


int getline_5_15(FILE * fp, char * str, int maxlen );

static char allocbuf[ALLOCSIZE];
static char * allocp = allocbuf;
char * alloc( int );


int readlines( FILE * fp, char * lineptr[], int maxlines );
void writelines( char * lineptr[], int nlines );
void qsort_ex_5_14( void *lineptr[], int left, int right, int ( * cmp )( void * , void * ) );
int numcmp( char *, char *);

void impl( char * path, int is_numeric, int is_case_insensitive );

int numcmp( char * a, char * b)
{
	return atof(a) < atof(b);
}

void swap( void * data[], int a, int b)
{
	void * tmp;
	tmp = data[a];
	data[a] = data[b];
	data[b] = tmp;
}

void qsort_ex_5_14( void *v[], int left, int right, int ( * cmp )( void * , void * ) )
{
	int i,
		last;
	if( left >= right )
		return;

	swap(v,left,(left+right)/2);
	last = left;
	for(i=left+1; i <=right; i++)
		if( (*cmp)(v[i], v[left]) < 0 )
			swap( v, ++last, i );
	swap( v, left, last);
	qsort_ex_5_14( v, left, last - 1, cmp);
	qsort_ex_5_14( v, last + 1, right, cmp);
}


int getline_5_15(FILE * fp, char * str, int maxlen )
{
	int c,
		i,
		maxlenMinusOne = maxlen - 1;

	for( i = 0;
			i < maxlenMinusOne &&
			(c = fgetc(fp)) != EOF  &&
			(c != '\n') ;
		++i )
	{
		str[i] = c;
	}
	if( c == '\n' )
		str[i++] = c;
	str[i] = '\0';
	return i	;
}

char * alloc( int size )
{
	if( allocbuf + ALLOCSIZE - allocp >= size )
	{
		allocp += size;
		return allocp - size;
	}
	return 0; //not enough room
}


int readlines( FILE * fp, char * lineptr[], int maxlines )
{
	int len,
		nlines = 0;
	char * p,
		line[MAXLEN];

	while( (len = getline_5_15(fp, line, MAXLEN)) > 0)
	{
		if(nlines >= maxlines || (p=alloc(len)) == NULL)
			return -1;
		line[len - 1] = '\0';
		strcpy( p, line);
		lineptr[ nlines++ ] = p;
	}
	return nlines;
}

void writelines( char * lineptr[], int nlines )
{
	for( int i = 0; i < nlines; i++ )
		printf("%s\n",lineptr[i] );
}

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	// todo use getopt or write own getopt
	int is_numeric = 0,
		is_case_insensitive = 0,
		opt;

	while( (opt = getopt(argc, argv, "nf")) != -1 )
	{
		switch (opt)
		{
			case 'n':
				printf("numeric sort\n");
				is_numeric = 1;
				break;
			case 'f':
				printf("case insensitive sort\n");
				is_case_insensitive = 1;
				break;
		}
	}

	while(--argc)
		if( *++argv  && *argv[0] != '-')
			impl(*argv, is_numeric, is_case_insensitive);
	return 0;
}

void impl( char * path, int is_numeric, int is_case_insensitive )
{
	FILE * fp = fopen(path,"rb");
	if( !fp )
	{
		perror(path);
		return;
	}


	int nlines = 0;

	char * lineptr[MAXLINES];
	if(  (nlines = readlines( fp, lineptr, MAXLINES)) >= 0 )
	{
		int (*comparator)(void*,void*) =
			is_numeric ?  (int(*)(void*,void*))numcmp :
			is_case_insensitive ?  (int(*)(void*,void*))strcasecmp :
				(int(*)(void*,void*))strcmp;
		qsort_ex_5_14( (void **)lineptr, 0, nlines - 1, comparator);
		writelines( lineptr, nlines);
	}
	else
	{
		printf("Error, too many lines to sort, max is %d\n",MAXLINES);
		return;
	}

	fclose(fp);
}
