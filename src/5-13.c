
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

const char * USAGE = "Write tail -n to print last n lines of input";


int tail( char * path, int num_lines );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	int num_lines = 10;
	char ** orig_argv = argv;
	int orig_argc = argc;
	if(argc < 2)
	{
		printf("Usage: tail [-n] file1 ... fileN\n");
		return -1;
	}
	while(--argc)
	{
		if( (*(++argv))[0] == '-' )
		{
			char * opt = argv[0];
			int n = atoi( opt+1 );
			if(n > 0)
				num_lines = n;
		}
	}

	argc = orig_argc;
	argv = orig_argv;
	while( --argc )
		if( (*(++argv))[0] != '-' )
			tail( *argv, num_lines );
	return 0;
}


int tail( char * path, int num_lines )
{
	FILE * fp;
	if( (fp = fopen(path,"rb")) == NULL )
	{
		perror(path);
		return -1;
	}

	int bufsize = 1024;
	char buf[bufsize];
	int c;
	int num_lines_found = 0;
	long pos;
	if( (pos = lseek(fp->_fileno,0L,SEEK_END)) == -1)
	{
		fprintf(stderr, "Error, first fseek of %s: %s\n",path,strerror(errno));
		return -1;
	}
	long endpos = ftell(fp);
	long seekpos = -1 * bufsize;
	char chars[bufsize];
	int bytesRead;
	char * charp;
	//printf("fseek first new pos %li endpos %li\n",pos,endpos);

	while( seekpos * -1 < endpos ) 
	{
		fseek(fp, seekpos , SEEK_END);
		//printf("after an fseek(%li), pos is %li\n",seekpos, ftell(fp));
		pos = 0;
		//printf("fseek to new pos %li endpos %li seekpos %li\n",pos,endpos,seekpos);
		bytesRead = 0;
		charp = chars;
		while( (bytesRead += read(fp->_fileno,charp,bufsize - bytesRead)) < bufsize )
		{
			//printf("read %d bytes\n",bytesRead );
			charp += bytesRead;
		}
		for(int i = bytesRead - 1; i > -1; i--)
		{
			if( (c = chars[i]) != '\n')
				continue;
			if( ++ num_lines_found == num_lines )
			{
				//printf("found %d new lines, need to position stream with endpos %li, seekpos %li, bytesRead %d, i %d\n",num_lines, endpos, seekpos, bytesRead, i);
				fseek(fp, (seekpos + i), SEEK_END);
				goto BREAKOUT;
			}
				
		}
		seekpos += (-1 * bufsize);
	}
	BREAKOUT:
	;
	while( ( c = fgetc(fp)) != EOF )
		printf("%c",c);

	return 0;
}

