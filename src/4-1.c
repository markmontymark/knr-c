
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write a strrindex(s,t) function that return the last occurrence of t in s or -1 if not found (this can be compared to rindex?)";

void impl( );
int strrindex(const char * s,char t);

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl();
	return 0;
}

void impl( )
{
	char * str = "This is a string we will test the last index for.";
	char t = 't';
	printf("Last index of %c in %s is %d\n",t,str,strrindex(str,t));

	t = 'z';
	printf("Last index of %c in %s is %d\n",t,str,strrindex(str,t));

	t = 'r';
	printf("Last index of %c in %s is %d\n",t,str,strrindex(str,t));

	t = 'r';
	printf("Last index of %c in %s is %d\n",t,"r",strrindex("r",t));

	t = 'z';
	printf("Last index of %c in %s is %d\n",t,"",strrindex("",t));
}


int strrindex(const char * s,char t)
{
	int len = strlen(s);
	while(--len > -1)
		if(s[len] == t)
			return len;
	return len;
}

