
#include "common.h"

const char * USAGE = "Remove all /* */ comments from a source file";

void impl( int argc, char ** argv );
void removeMultilineComment( char * filename );

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl(argc,argv);
	return 0;
}

void impl(int argc, char ** argv )
{
	for( int i = 1; i < 	argc ; i++ )
		removeMultilineComment( argv[i] );
}

void removeMultilineComment( char * filename )
{
	FILE * fp = fopen(filename,"rb");
	if( !fp )
	{
		fprintf(stderr,"Error opening file %s, %s\n",filename,strerror(errno));
		return;
	}

	int commentState = 0; // 0 == before first /, 1 == before first *, 2 == before second *, 3 == before /
	int MAX_CHARS = 1024;
	int nCharsRead;
	char buf[MAX_CHARS];
	char * charsRead;
	char lastChar;
	char curChar;
	
	//while( (charsRead = fgets(buf,MAX_CHARS,fp)) != NULL )
	while( fread(buf,1,MAX_CHARS,fp) )
	{
		int i = 0;
		while( buf[i] != '\0')
		{
			curChar = buf[i];
			i++;
			switch(commentState)
			{
				case 0:
					if(curChar == '/')
					{
						lastChar = curChar;
						commentState = 1;
					}
					else fputc(curChar,stdout);
					break;

				case 1:
					if(curChar == '*')
						commentState = 2;

					else
					{
						fputc(lastChar,stdout);
						fputc(curChar,stdout);
						commentState = 0;
					}
					break;

				case 2:
					if(curChar == '*')
					{
						lastChar = curChar;
						commentState = 3;
					}
					break;

				case 3:
					commentState = curChar == '/' ? 0 : 2;
					break;

				default:
					fprintf(stderr,"%s\n","Should never get here");
			}
		}
	}
}

