
// This file auto-generated on Tue Aug 21 13:50:45 2012

//#include "common.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "arraylist_str.h"


const char * USAGE = "Write a sort() to sort lines, allow for an n arg that sorts by field number n";

void impl( char * path );

void sort( char ** lines, int field );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	if(argc < 2)
		return 0;
	for(int i = 1; i < argc ; i++)
		impl(*++argv);
	return 0;
}

void impl( char * path )
{
	FILE * fp = fopen(path,"rb");
	if( !fp )
	{
		fprintf(stderr,"Error opening file %s, %s\n", path, strerror(errno) );
		return;
	}

	printf("Processing %s\n",path);

	int MAX_CHARS = 1024;
	int MAX_LINES = 1024;
   char buf[MAX_CHARS];
	char llines[MAX_LINES][MAX_CHARS];
   int nCharsRead;
   char * charsRead;
   char curChar;
	int lineno = 0;

	arraylist_str_t * lines = arraylist_str_new();
	
   while( (charsRead = fgets(buf,MAX_CHARS,fp)) != NULL )
   {
		lineno++;
      nCharsRead = strlen(charsRead);
	}

	if( fclose(fp) )
	{
		fprintf(stderr,"Error closing file %s, %s\n", path, strerror(errno) );
		return;
	}

}

void sort( char ** lines, int field )
{
}

