
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

	if(argc < 2)
	{
		printf("Usage: tail [-n] file1 ... fileN\n");
		return EXIT_FAILURE;
	}

	char ** orig_argv = argv;
	int orig_argc = argc;
	int num_lines = 10;

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

	num_lines++; // go for one more than asked so that when n + 1 is found, we're fgetc-d to the right position in stream to dump rest of fgetc to stdout

	int retval;
	while( --argc )
		if( (*(++argv))[0] != '-' && (retval = tail( *argv, num_lines ))  == EXIT_FAILURE )
			; // ignore failure, keep processing args
	return EXIT_SUCCESS;
}


int tail( char * path, int num_lines )
{
	FILE * fp;
	if( (fp = fopen(path,"rb")) == NULL )
	{
		perror(path);
		return EXIT_FAILURE;
	}

	int bufsize = 1024;
	char buf[bufsize];
	int c;
	int num_lines_found = 0;
	long pos;
	if( (pos = lseek(fp->_fileno,0L,SEEK_END)) == -1)
	{
		fprintf(stderr, "Error, first fseek of %s: %s\n",path,strerror(errno));
		return EXIT_FAILURE;
	}
	long endpos = ftell(fp);
	long seekpos = -1 * bufsize;
	char chars[bufsize];
	int bytesRead;
	char * charp;
	//printf("fseek first new pos %li endpos %li seekpos %li\n",pos,endpos,seekpos);

	int found_n_lines = 0;
	do
	{
		if( (-1 * seekpos) > endpos )
			seekpos = -1 * endpos;
		
		if( (fseek(fp, seekpos, SEEK_END)) == -1 )
		{
			fprintf(stderr, "Error, fseek of %s: %s\n",path,strerror(errno));
			return EXIT_FAILURE;
		}
		//printf("after an fseek(%li), pos is %li\n",seekpos, ftell(fp));
		pos = 0;
		//printf("fseek to new pos %li endpos %li seekpos %li\n",pos,endpos,seekpos);
		bytesRead = 0;
		charp = chars;
		while( (bytesRead += read(fp->_fileno,charp,bufsize - bytesRead)) < (-1*seekpos) )
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
				fseek(fp, (seekpos + i + 1), SEEK_END); // +1 because we're at the nth new line
				found_n_lines = 1;
				goto BREAKOUT;
			}
		}
		if( (-1 * seekpos) == endpos)
			goto BREAKOUT;
		seekpos += (-1 * bufsize);
	}
	while( (-1 * seekpos) < endpos ) ;
	BREAKOUT:
	;
	if( ! found_n_lines )
		fseek(fp,0L,SEEK_SET);

	while( ( c = fgetc(fp)) != EOF )
		printf("%c",c);

	return EXIT_SUCCESS;
}

