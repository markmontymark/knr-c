#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "strings.h"
#include "unistd.h"
#include "getopt.h"
#include "ctype.h"

const char * USAGE = "Add a field handling capability, so sorting may be done on fields within lines, each field sorted according to an independent set of options. (The index for this book was sorted -df for the index category and -n for the page numbers.)";


#define MAXLINES 5000
#define MAXLEN 5000
#define ALLOCSIZE 100000

int IS_NUMERIC = 0;
int IS_CASE_INSENSITIVE = 0;
int IS_DICTIONARY = 0;

int IS_NUMERIC_FIELD = 0;
int IS_CASE_INSENSITIVE_FIELD = 0;
int IS_DICTIONARY_FIELD = 0;


int getline_(FILE * fp, char * str, int maxlen );

static char allocbuf[ALLOCSIZE];
static char * allocp = allocbuf;
char * alloc( int );


int readlines( FILE * fp, char * lineptr[], int maxlines );
void writelines( char * lineptr[], int nlines );
void qsort_ex_5_14( void *lineptr[], int left, int right, int ( * cmp )( void * , void * ) );
int numcmp( char *, char *);
int numfieldcmp( char * , char * );
int strDirectoryOrdercmp( char *, char *);
int strDirectoryOrderFieldcmp( char *, char *);
char * get_field( char *, int );


int strcaseFieldcmp( char *, char *);


void impl( char * path );

char * get_field( char * line, int field )
{
	int f = 1;
	while( isblank(*line) && ++line)
		;
	if( *line == '\0' )
		return line;
	for( ; *line; )
	{
		if( f == field )
			return line;
		if( isblank(*line) )
		{
			f++;
			while( *++line && isblank(*line))
				;
		}
		else
			line++;
	}
	return "";
}

int strcaseFieldcmp( char * aline, char * bline)
{
	char * a = get_field(aline, IS_CASE_INSENSITIVE_FIELD);
	char * b = get_field(bline, IS_CASE_INSENSITIVE_FIELD);
	return strcasecmp(a,b);
}


int numcmp( char * a, char * b)
{
	//printf("numcmp got fields, a=%s,b=%s, converted is a=%f, b=%f\n",a,b,atof(a),atof(b));
	float fa = atof(a);
	float fb = atof(b);
	return fa == fb ? 0 : fa < fb ? -1 : 1;
}

int numfieldcmp( char * aline, char * bline)
{
	char * a = get_field(aline, IS_NUMERIC_FIELD);
	char * b = get_field(bline, IS_NUMERIC_FIELD);
	return numcmp(a,b);
}

int strDirectoryOrdercmp( char * a, char * b)
{
	int ai = 0,
		bi = 0;


	while( ! isalnum(a[ai]) && ! isblank(a[ai]) && a[ai])
		++ai;
	while( ! isalnum(b[bi]) && ! isblank(b[bi]) && b[bi])
		++bi;

	while( IS_CASE_INSENSITIVE ? (tolower(a[ai]) == tolower(b[bi])) : (a[ai] == b[bi]) )
	{
		if( a[ai] == '\0' )
			return 0;
		if( ! isalnum(a[ai]) && ! isblank(a[ai]) && a[ai])
			while( ! isalnum(a[ai]) && ! isblank(a[ai]) && a[ai])
				++ai;
		else
			ai++;

		if( ! isalnum(b[bi]) && ! isblank(b[bi]) && b[bi])
			while( ! isalnum(b[bi]) && ! isblank(b[bi]) && b[bi])
				++bi;
		else
			bi++;
	}
	return IS_CASE_INSENSITIVE ? (tolower(a[ai]) - tolower(b[bi])) : (a[ai] - b[bi]);
}
int strDirectoryOrderFieldcmp( char * aline, char * bline)
{
	char * a = get_field(aline, IS_DICTIONARY_FIELD);
	char * b = get_field(bline, IS_DICTIONARY_FIELD);
	return strDirectoryOrdercmp(a,b);
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


int getline_(FILE * fp, char * str, int maxlen )
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

	while( (len = getline_(fp, line, MAXLEN)) > 0)
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
	int opt;
	int has_field_specific_sort = 0;

	int orig_argc = argc;
	char ** orig_argv = argv;
	int dict_fieldno = 0;
	int numeric_fieldno = 0;
	int case_fieldno = 0;

	while( --argc )
	{
		if( (*++argv)[0] == '-')
		{
			char c = (*argv)[1];
			int fieldno = atoi( (*argv)+2);
			switch(c)
			{
				case 'd':
					printf("dictionary sort\n");
					IS_DICTIONARY = 1;
					if(fieldno != 0)
						IS_DICTIONARY_FIELD = fieldno;
					break;
				case 'n':
					printf("numeric sort\n");
					IS_NUMERIC = 1;
					if(fieldno != 0)
					{
						IS_NUMERIC_FIELD = fieldno;
						printf("numeric sort field %d\n", IS_NUMERIC_FIELD);
					}
					break;
				case 'f':
					IS_CASE_INSENSITIVE = 1;
					printf("case insensitive sort\n");
					if(fieldno != 0)
						IS_CASE_INSENSITIVE_FIELD = fieldno;
					break;
			}
		}
	}

	argc = orig_argc;
	argv = orig_argv;

	while(--argc)
		if( *++argv  && (*argv)[0] != '-')
			impl(*argv);
	return 0;
}

void impl( char * path )
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
			IS_NUMERIC ? (IS_NUMERIC_FIELD ? ((int(*)(void*,void*))numfieldcmp) : ((int(*)(void*,void*))numcmp) ) :
			IS_DICTIONARY ? (IS_DICTIONARY_FIELD ? ((int(*)(void*,void*))strDirectoryOrderFieldcmp) : ((int(*)(void*,void*))strDirectoryOrdercmp) ) :
			IS_CASE_INSENSITIVE ? (IS_CASE_INSENSITIVE_FIELD ? ((int(*)(void*,void*))strcaseFieldcmp) : ((int(*)(void*,void*))strcasecmp) ) :
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
