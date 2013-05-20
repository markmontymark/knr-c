
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"
#include <fcntl.h>

const char * USAGE = "Rewrite cat with read/write/open/close instead of standard library equivalents. Which is faster, my own cat or the real cat?\n";

int _cat( int fd_in);
int cat( char * inpath);

const int MAX_READ = 8192; // get page size w/ a syscall

int main( int argc, char ** argv )
{
	size_t USAGE_LEN = strlen( USAGE );
	if( write(STDOUT_FILENO, USAGE, USAGE_LEN ) == -1 )
	{
		fprintf(stderr,"Error writing %s: %s\n", USAGE, strerror(errno));
		return errno;
	}
	if( argc < 2 )
		return _cat(STDIN_FILENO);

	int retval;
	for(int i = 1; i < argc; i++)
		if( (retval = cat( argv[i] )) )
			return retval;
	return 0;
}

int cat( char * inpath )
{
	int fd_in;
	if( (fd_in = open(inpath,O_RDONLY,0)) == -1  )
	{
		fprintf(stderr,"Error opening %s file for read: %s\n",inpath, strerror(errno));
		return errno;
	}
	_cat( fd_in );
	if( close( fd_in ) )
	{
		fprintf(stderr,"Error closing %s file for read: %s\n",inpath, strerror(errno));
		return errno;
	}
	return 0;
}


int _cat( int fd_in )
{
	ssize_t bytesRead;
	ssize_t bytesWritten;
	char buf[MAX_READ];
	while(  (bytesRead = read(fd_in, buf, MAX_READ) ) )
	{
		if(  ( bytesWritten = write( STDOUT_FILENO, buf, bytesRead)) == -1 )
		{
			fprintf(stderr,"Error writing %s: %s\n", buf, strerror(errno));
			return errno;
		}
	}
	if( bytesRead == -1 )
	{
		fprintf(stderr,"Error reading from fd %d: %s\n", fd_in, strerror(errno));
		return errno;
	}
	
	return 0;
}
