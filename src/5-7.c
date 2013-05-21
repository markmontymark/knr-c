
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Rewrite readlines() to store lines provided by main() rather than calling alloc. Benchmark the difference..which is better?";

#define MAXLEN  10000
#define MAXLINE  1000
#define ALLOCSIZE ((MAXLEN) * (MAXLINE))


int getline ( char *, int);
int orig_readlines( char **, int);
int readlines( char **, char *, char *, char *, int);
char * alloc(char [], char *, int);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	char allocbuf[ALLOCSIZE];
	char * allocp = allocbuf;
	char * lines[MAXLINE];
	char line[MAXLEN];
	int nlines = readlines(lines,line,allocbuf,allocp,MAXLINE);
	printf("Read %d lines\n",nlines);
	return 0;
}

int readlines(char ** lineptr, char * line, char * allocbuf, char * allocp, int maxlines)
{
	int len,
		nlines;
	char * p;
	
	nlines = 0;

	while( (len = getline(line,MAXLEN)) > 0 )
	{
		if( nlines >= maxlines || (p=alloc(allocbuf,allocp,len)) == NULL)
			return -1;
		else
		{
			line[len - 1] = '\0'; // delete newline
			strcpy(p,line);
			lineptr[ nlines++ ] = p;
			
		}
	}
	return nlines;
}

int getline( char * line, int limit)
{
	int c,
		i;
	
	for( i = 0; i < MAXLINE - 1 &&
			(c=getchar()) != EOF && c != '\n';
			i++)
	{
		line[i] = c;
	}
	if( c == '\n')
	{
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	return i;
}

char * alloc( char * allocbuf, char * allocp, int length)
{
	if( allocbuf + ALLOCSIZE - allocp >= length )
	{
		allocp += length;
		return allocp - length;
	}
	else return 0;	
}
