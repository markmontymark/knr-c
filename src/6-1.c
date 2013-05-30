

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Update getword to handle underscores, string constants, comments, preprocessor control lines";

void impl( );

#define GETCH_BUF_MAXSIZE 100
typedef struct getch_buf getch_buf_t;
struct getch_buf {
	char * buf;
	int bufp;
};
#define getch_buf_s sizeof(getch_buf_t)

int getch(getch_buf_t *);
void ungetch(getch_buf_t *, int);

getch_buf_t * getch_buf_new()
{
	getch_buf_t * newptr = malloc(getch_buf_s);
	if(newptr == NULL)
		fprintf(stderr,"Can't malloc a new getch_buf_t\n");
	newptr->bufp = 0;
	newptr->buf = malloc(GETCH_BUF_MAXSIZE);
	if(newptr->buf == NULL)
		fprintf(stderr,"Can't malloc a new getch_buf_t->buf\n");
	return newptr;
}
void getch_buf_free(getch_buf_t * buf)
{
	if(buf == NULL)
		return;
	if( buf->buf != NULL)
		free(buf->buf);
	free(buf);	
}


int getword( char * word, getch_buf_t * buf, int limit);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
	char * word = malloc(GETCH_BUF_MAXSIZE);
	getch_buf_t * buf = getch_buf_new();
	while( getword( word, buf, GETCH_BUF_MAXSIZE))
	{
		if( strcmp(word,"") == 0 )
			break;
		printf("got word: %s\n",word);
	}
	getch_buf_free( buf );
	free(word);
}

int getch(getch_buf_t * buf)
{
	return (buf->bufp > 0) ? buf->buf[--(buf->bufp)] : fgetc(stdin);
}

void ungetch(getch_buf_t * buf, int c)
{
	if( buf->bufp >= GETCH_BUF_MAXSIZE )
	{
		printf( "ungetch: too many chars\n");
		return;
	}
	buf->buf[buf->bufp++] = c;
}

int getword( char * word, getch_buf_t * buf, int limit)
{
	int c, 
		do_return_with_nextgetword_call = 0,
		is_string_literal = 0,
		string_literal_delim,
		string_literal_escape = '\\',
		lastSpaceWasNewline = 0;
	char * w = word;

	while( isspace( c = getch(buf) ) )
	{
		lastSpaceWasNewline = c == '\n';
	}

	if( lastSpaceWasNewline && c == '#')
	{
		while( (c = getch(buf)) != EOF && c != '\n' )
			;
		return getword(word,buf,GETCH_BUF_MAXSIZE);
	}

	if( c != EOF )
	{
		// starting a string literal
		if( c == '\'' || c == '"')
		{
			is_string_literal = 1;
			string_literal_delim = c;
		}
		
		// maybe starting a comment, check next char
		else if (c == '/')
		{
			int nextC = getch(buf);
			if(nextC == EOF)
			{
				*w++ = c;
				*w = '\0';
				return word[0];
			}
			// starting a single line comment, basically just wind off STDIN till we hit a newline and return what's been stored in word so far
			if(nextC == '/')
			{
				while( (nextC = getch(buf)) != EOF && nextC != '\n')
					;
				*w ='\0';
				return getword( word, buf, GETCH_BUF_MAXSIZE);//word[0];
			}

			// starting a multiline comment
			else if(nextC == '*')
			{
				int nextnextC = 0;
				while( (nextC = getch(buf)) != EOF)
				{
					if( nextC == '*' && (nextnextC = getch(buf)) == '/')
					{
						do_return_with_nextgetword_call = 1;
						break;
					}
				}
				if(nextC == EOF || nextnextC == EOF)
				{
					*w = '\0';
					return getword( word, buf, GETCH_BUF_MAXSIZE);//word[0];
				}
			}
		}
		else
			*w++ = c;
	}

	if(do_return_with_nextgetword_call)
		return getword(word,buf,GETCH_BUF_MAXSIZE);


	if (c != '_' && ! is_string_literal && ! isalpha(c))
	{
		*w = '\0';
		return c;
	}

	for( ; --limit > 0 ; w++ )
	{
		if (! isalnum(*w = getch(buf) ))
		{
			if( *w == '_' )
				continue;

			if( *w == string_literal_delim)
			{
				if( *(w-1) == string_literal_escape )
				{
					// Replaced escaped quote in string literal to just quote, so "asdf\"123" becomes asdf"123
					*(w-1) = *w;
					*w = '\0';
					continue;
				}
				else
				{
					// found end of string literal
					*w = '\0';
					break;
				}
			}
			else if(is_string_literal)
				continue;

			else if (*w == '/')
			{
				int nextC = getch(buf);
				if(nextC == EOF)
				{
					*++w = '\0';
					return word[0];
				}
				// starting a single line comment, basically just wind off STDIN till we hit a newline and return what's been stored in word so far
				if(nextC == '/')
				{
					while( (nextC = getch(buf)) != EOF && nextC != '\n')
						;
					*w ='\0';
					return word[0];
					//return getword( word, buf, GETCH_BUF_MAXSIZE);//word[0];
				}

				// starting a multiline comment
				else if(nextC == '*')
				{
					*w ='\0';
					int nextnextC = 0;
					while( (nextC = getch(buf)) != EOF)
					{
						if( nextC == '*' && (nextnextC = getch(buf)) == '/')
						{
							do_return_with_nextgetword_call = 1;
							break;
						}
					}
					if(nextC == EOF || nextnextC == EOF)
					{
						*w = '\0';
						return getword( word, buf, GETCH_BUF_MAXSIZE);//word[0];
					}
				}
			}
			if( do_return_with_nextgetword_call )
				return word[0];
			ungetch(buf,*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}
