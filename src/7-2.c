
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "\n\
Write a program to print its input in a sensible way: \n\
sensible means - indented and max line length (72 chars) \n\
- replace non-graphic chars with hexadecimal representation \n\
according to local (locale?) custom";

const int MAX_LINE_LENGTH = 72;
const char * PRINTABLE = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 !\"#%&'()*+,-./:;<=>?[\\]^_{|}~\t\f\v\r\n";

void impl( char * );
void encode_weirdness_to_hex_str(char * ,int);
void char_to_hex_str(char * dest, char c);


int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	while( *++argv )
		impl( *argv );
	return 0;
}

void impl( char * filename )
{
	FILE * f = strcmp(filename,"-") ? fopen(filename,"rb") : stdin;
	char line[MAX_LINE_LENGTH];
	char * charsRead;
	int n_charsRead;
	int chars_to_read = MAX_LINE_LENGTH;
	while( (charsRead = fgets(line,chars_to_read,f)) != NULL )
	{
		n_charsRead = strlen(charsRead) ;
		if( *(charsRead+n_charsRead-1) == '\n')
		{
			encode_weirdness_to_hex_str(charsRead,0);
			chars_to_read = MAX_LINE_LENGTH;
			continue;
		}

		// handle split lines
		char last_word[MAX_LINE_LENGTH];
		int last_word_startpos = MAX_LINE_LENGTH;
		while( --last_word_startpos
			&& ! isspace( *(charsRead + last_word_startpos)) )
			;
		if(last_word_startpos)
		{
			char start_sentence[last_word_startpos+1];
			strncpy(start_sentence,charsRead,last_word_startpos);
			start_sentence[last_word_startpos] = '\0';
			char * last_word = charsRead + last_word_startpos;
			encode_weirdness_to_hex_str(start_sentence,1);
			encode_weirdness_to_hex_str(last_word+1,0);
			chars_to_read = MAX_LINE_LENGTH - strlen(last_word);
		}
		else
		{
			encode_weirdness_to_hex_str(charsRead,1);
			chars_to_read = MAX_LINE_LENGTH;
		}
		
	}
	fclose(f);
}

void encode_weirdness_to_hex_str(char * s, int print_newline)
{
	do
	{
		if(index(PRINTABLE,*s))
			fputc(*s,stdout);
		else
		{
		}
	}	
	while( *++s );

	if(print_newline)
		fputc('\n',stdout);
}

void char_to_hex_str(char * dest, char c)
{
}
