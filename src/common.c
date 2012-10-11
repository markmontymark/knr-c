
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#include "common.h"

const char * get_home_dir()
{
	return getenv("HOME");
}

void get_rcfile(char * dest, const char * progname)
{
	snprintf(dest,
		256,
		"%s/.%src",
		get_home_dir(),
		progname);
}

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

void usage(const char * usage_msg, const char * progname)
{
   char rcFilename[256];
   get_rcfile(rcFilename,progname);
	fprintf(stderr,"\
Program: %s\n\
Purpose: %s\n\
data file readable (data/%s): %s\n\
rc file: %s\n",
		progname,
		usage_msg,
		progname,
		can_open_data_file(progname) ? "yes" : "no",
		rcFilename
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


int read_line(char ** dest, int realloc_size, FILE *fp) 
{
	char *t=NULL, *p=NULL;
	int c; /* character buffer */
	int len = 0; /* current number of elements read and stored */
	int allocated = 0; /* number of allocated bytes in p */

	p = malloc(realloc_size);
	if(p == NULL)
		return -1;

	allocated = realloc_size;

	while( 
		(c = fgetc(fp)) != EOF 
		&& c != '\n'
	)
	{
		if(len == allocated) 
		{
			t = realloc(p, allocated + realloc_size);
			if (t == NULL)
			{
				free(p);
				return -1;
			}
			p = t;
			allocated += realloc_size;
		}
		p[len++] = (char) c;
	}
	if(len == 0) 
	{
		if(c == EOF) 
		{
			free(p);
			return -1;
		} 
		else 
		{
			assert(c == '\n');
			p[0] = '\0';
			*dest = p;
			return 0;
		}
	}

	if( (len + 1) != allocated) 
	{
		t = realloc(p, len+1);
		if (t == NULL) 
		{
			if(p)
				free(p);
			return -1;
		}
		p = t;
	}

	p[len] = '\0';
	*dest = p;
	return len;
}

