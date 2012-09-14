
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wchar.h>
#include "common.h"

const char * USAGE = "Write a program to print out ranges of char, short, int, long vars (both signed and unsigned)";

void impl( );

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
	char c = '\0';
	unsigned char cu = '\0';
	short s = 1;
	unsigned short su = 1;
	int i = 1;
	unsigned int iu = 1;
	long l = 1;
	unsigned long lu = 1;

	wchar_t w = L'\0';

	long long mx = 10;
	long long mn = 0;

	while( ++c > 0) mx = c;
	c = '\0';
	while( --c < 0) mn = c;
	mn = ++c;
	printf("char range is %lli to %lli\n",mn,mx);

	while( ++w > 0) mx = w;
	w = '\0';
	while( --w < 0) mn = w;
	mn = ++w;
	printf("wchar range is %lli to %lli\n",mn,mx);

	while( ++cu > 0) mx = cu;
	cu = '\0';
	while( --cu < 0) mn = cu;
	mn = ++cu;
	printf("unsigned char range is %lli to %lli\n",mn,mx);

	while( ++s > 0) mx = s;
	s = 0;
	while( --s < 0) mn = s;
	mn = ++s;
	printf("short range is %lli to %lli\n",mn,mx);

	while( ++su > 0) mx = su;
	su = 0;
	while( --su < 0) mn = su;
	mn = ++su;
	printf("unsigned short range is %lli to %lli\n",mn,mx);
	
	while( ++i > 0) mx = i;
	i = 0;
	while( --i < 0) mn = i;
	mn = ++i;
	printf("int range is %lli to %lli\n",mn,mx);

	while( ++iu > 0) mx = iu;
	iu = 0;
	while( --iu < 0) mn = iu;
	mn = ++iu;
	printf("unsigned int range is %lli to %lli\n",mn,mx);
	
	while( ++l > 0) mx = l;
	l = 0;
	while( --l < 0) mn = l;
	mn = ++l;
	printf("long range is %lli to %lli\n",mn,mx);

	while( ++lu > 0) mx = lu;
	lu = 0;
	while( --lu < 0) mn = lu;
	mn = ++lu;
	printf("unsigned long range is %lli to %lli\n",mn,mx);
	
	
}

