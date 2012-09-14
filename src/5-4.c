
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write strend (better called endsWith(str,substr)) that returns 1 if str ends with substr";

void impl( );

int endsWith(const char * s, const char * substr);

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
	const char * src = "This is a sentence";
	const char * substr1 = "ence";
	const char * substr2 = "sentence";

	printf("%s endsWith %s? %s\n", src,substr1, endsWith(src,substr1) ? "yes" : "no");
	printf("%s endsWith %s? %s\n", src,"wrong", endsWith(src,"wrong") ? "yes" : "no");
	printf("%s endsWith %s? %s\n", src,substr2, endsWith(src,substr2) ? "yes" : "no");
	printf("%s endsWith %s? %s\n", "",".", endsWith("",".") ? "yes" : "no");
	printf("%s endsWith %s? %s\n", "","", endsWith("","") ? "yes" : "no");
	printf("%s endsWith %s? %s\n", "a","a", endsWith("a","a") ? "yes" : "no");
	
}

int endsWith(const char * s, const char * substr)
{
	if( s == NULL || substr == NULL)
		return 0;

	int sublen = strlen(substr);
	int slen = strlen(s);
	if(sublen > slen)
		return 0;

	while( --slen > -1 && --sublen > -1 && s[slen] == substr[sublen])
		;
	if(slen == -1 && sublen == 0 || (sublen == -1))
		return 1;
	return 0;
}
