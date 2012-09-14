
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

const char * USAGE = "Write an atof function that handles scientific notation";

void impl( );
int strrindex(const char * s,char t);
char * substring(const char * src,int from, int to);
double scientific_notation_to_double(char * str);

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
	char * nums[7];
	nums[0] = "1";
	nums[1] = "12";
	nums[2] = "1.2";
	nums[3] = ".1";
	nums[4] = ".12";
	nums[5] = "0.1";
	nums[6] = "0.12";

	char * es[6];
	es[0] = "e";
	es[1] = "E";
	es[2] = "-e";
	es[3] = "+e";
	es[4] = "-E";
	es[5] = "+E";

	char * exps[3];
	exps[0] = "1";
	exps[1] = "12";
	exps[2] = "0";

	char * str = malloc( 80 );
	for(int i = 0; i < 7; i++)
	{
		for(int j = 0; j < /*6*/6; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				snprintf(str,
					80,
					"%s%s%s",nums[i],es[j],exps[k] );
				printf("local_atof(%s) = %f\n", str, scientific_notation_to_double(str)); 
			}
		}
	}

}

double scientific_notation_to_double(char * str)
{
	int has_sign = strrindex(str,'+');
	if( has_sign == -1) // this is an int
		has_sign = strrindex(str,'-');
	
	int has_exponent = strrindex(str,'E');
	if( has_exponent  == -1) // this is an int
		has_exponent = strrindex(str,'e');

	char * signPart = "+";
	if( has_sign == -1 && has_exponent != -1)
		has_sign = has_exponent;
	else
		signPart = substring(str,has_sign,has_sign+1);

	char * numPart = substring(str,0,has_sign);
	char * expPart = substring(str,has_exponent+1,strlen(str));
	double retval;
	retval = ( strrindex(numPart,'.') != -1) ?  atof(numPart) : (double)atoi(numPart);

	double exp = 1;
	int expNum = atoi(expPart);
	while(expNum-- > 0)
		exp *= 10;
	if(signPart[0] == '-')
		exp =  1/exp;
	//printf("%s: has_sign %d, has_exp %d, parts %s and %s and %s, strlen(str) = %d, sizeof str = %d\n\n\n", 
		//str, has_sign, has_exponent, numPart, signPart, expPart, strlen(str), sizeof(str));
	return retval * exp;//1.0;
}


int strrindex(const char * s,char t)
{
	int len = strlen(s);
	while(--len > -1)
		if(s[len] == t)
			return len;
	return len;
}

char * substring(const char * src,int from, int to)
{
	int len = strlen(src);
	//	printf("substring(%s,%d,%d), len %d\n",src,from,to,len);
	if(to > len)
		return NULL;
	if(from >= to)
		return NULL;

	char * retvalStr = malloc( (to-from) + 1);
	char * retval = retvalStr;
	for(int i = from; i < to; i++)
	{
		*retvalStr = src[i];
		retvalStr++;
	}
	*retvalStr = '\0';
	return retval;
}


