
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const char * USAGE = "Print all input lines longer than <argv[1]>chars";

int can_open_data_file(const char * progname)
{
	char datafile[256];
	snprintf(datafile,256,"%s/%s","data",progname);
	FILE * fp;
	if( (fp = fopen(datafile,"rb")))
	{
		fclose(fp);
		return 1;
	}
	return 0;
}

void usage(const char * progname)
{
	printf(
		"Program: %s\nPurpose: %s\nData file readable (data/%s): %s\n",
		progname,USAGE,progname,
		can_open_data_file(progname) ? "yes" : "no"
	);
}

void get_progname(char * path)
{
   char * retval;
   int tries = 3;
   while( --tries && (retval = rindex(path,'/')) != NULL)
      path = strcpy(path,retval+1);
}


int open_data_file(const char * progname,FILE * fp)
{
	char datafile[256];
	snprintf(datafile,256,"%s/%s","data",progname);
	if( (fp = fopen(datafile,"rb")))
		return 1;

	fprintf(stderr,"Can't open data file %s, %s\n",datafile,strerror(errno));
	return 0;
}

void close_data_file(FILE * fp)
{
	if( ! fp )
		return;
	fclose(fp);
}

void impl( char * progname , int max_line_length );

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(progname);
	int max_line_length = 256;
	if(argc > 1)
		max_line_length = atoi(argv[1]);
	printf("Max line length %d\n",max_line_length);
	impl(progname, max_line_length);
	return 0;
}

void impl( char * progname , int max_line_length  )
{
	//const char * USAGE = "Print all input lines longer than 80 characters";
	int nCharsRead;
	int maxRead = max_line_length - 1;
	char buf[max_line_length];
	char * charsRead;
	while( (charsRead = fgets(buf,max_line_length,stdin)) != NULL )
	{
		nCharsRead = strlen(charsRead);
		if(nCharsRead == maxRead &&
			charsRead[nCharsRead] != '\n')
		{
			printf("long line: %s\n",charsRead);
		}
		else
		{
			printf("not long line: %s %d\n",charsRead, strlen(charsRead));
		}
	}
}

