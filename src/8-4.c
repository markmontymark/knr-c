
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

const char * USAGE = "fseek is identical to lseek, except that fseek takes a file pointer, not a file descriptor. Write fseek.";

void impl( char * path );

#undef fseek
int fseek( FILE * fp, long int offset, int origin)
{
#ifdef __APPLE__
	return lseek( fp->_file, offset, origin );
#else
	return lseek( fp->_fileno, offset, origin );
#endif
}

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	while( --argc )
		impl( *++argv );
}

void impl( char * path )
{
	if( path == NULL )
	{
		fprintf(stderr,"Passing null to impl, nothing to do\n");
		return;
	}

	FILE * fp;
	if(  (fp = fopen(path,"rb")) == NULL)
	{
		perror(path);
		return;
	}
	printf("%s opened\n", path);

	if( fseek( fp, 0L, 0 ) == -1 )
	{
		perror(path);
		return;
	}
	printf("%s fseek to 0,0\n", path);

	char buf[2];
#ifdef __APPLE__
	if( read(fp->_file, &buf, 1) == -1 )
#else
	if( read(fp->_fileno, &buf, 1) == -1 )
#endif
	{
		perror("Error on reading a buf[2]");
		return;
	}
	printf("%s read a char %s\n", path, buf );

	if( fseek( fp, 3L, 0 ) == -1 )
	{
		perror(path);
		return;
	}
	printf("%s fseek to 3,0\n", path);

#ifdef __APPLE__
	if( read(fp->_file, &buf, 1) == -1 )
#else
	if( read(fp->_fileno, &buf, 1) == -1 )
#endif
	{
		perror("Error on reading a buf[2]");
		return;
	}
	printf("%s read a char %s\n", path, buf );


	if( fseek( fp, 6L, 0 ) == -1 )
	{
		perror(path);
		return;
	}
	printf("%s fseek to 6,0\n", path);

#ifdef __APPLE__
	if( read(fp->_file, &buf, 1) == -1 )
#else
	if( read(fp->_fileno, &buf, 1) == -1 )
#endif
	{
		perror("Error on reading a buf[2]");
		return;
	}
	printf("%s read a char %s\n", path, buf );


	if( fclose(fp) )
	{
		perror(path);
		return;
	}
	printf("%s closed\n", path );


}

