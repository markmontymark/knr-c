
#include "common.h"

const char * USAGE = "Remove trailing whitespace (except newline) from input lines and delete blank lines";

int is_blank_line(char * line);
char * remove_trailing_spaces(char * line);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
	int max = 25;
	char *line[0];
	
	while( read_line(line,max,stdin) != -1 )
	{
		if( is_blank_line( *line) )
			continue;
		*line = remove_trailing_spaces( *line);
		fprintf(stdout,"%s\n",*line);
	}
}

char * remove_trailing_spaces(char * line)
{
	int last_space_idx = -1;
	int len = strlen( line );

	if(len < 1 )
		return line;

	int i = len;
		
	while( --i > -1 && line[i] == ' ') 
		;

	if( i != (len - 1))
	{
		char * linecopy = malloc( len );
		strncat(linecopy,line,i+1);
		return linecopy;
	}
	return line;
}

int is_blank_line(char * line)
{
	if(line == NULL)
		return 1;

	for(int i = 0; line[i]; i++)
		if(line[i] != ' ')
			return 0;

	return 1;
}

