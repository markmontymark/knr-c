
#include "common.h"

const char * USAGE = "Write a pointer based version of strcat(dest,src)";

void impl( );

char * mystrcat(char * dest, char * src) ;

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
	char * dest = "a";// = &dest_storage[0];
	char * src1 = "b";
	char * src2 = "str2";
	char * src3 = "str3";
	char * res;
	char * res2;

	printf("concatenate %s to end of %s = ",src1,dest);
	res = mystrcat(dest,src1);
	printf("%s\n",res);

	printf("concatenate %s to end of %s = ",src2,res);
	res2 = mystrcat(res,src2);
	printf("%s\n",res2);
	free(res);
	free(res2);

	printf("concatenate %s to end of %s = ",src2,src3);
	res = mystrcat(src3,src2);
	printf("%s\n",res);
	free(res);
}


char * mystrcat(char * dest, char * src) 
{
	int dlen = strlen(dest);	
	int slen = strlen(src);	
	char * p = NULL;
	p = malloc(dlen * sizeof(char));
	int i = 0;
	while( *dest != '\0')
	{
		*p++ = *dest++;
		i++;
	}
	dest -= i;
	p -= i;	
	char * t = realloc(p, (dlen+slen) * sizeof(char)  + 1);
   if (t == NULL)
   {
      free(p);
      return NULL;
   }
   p = t;
	p += i;

	while( *p++ = *src++ )
		;

	p -= (dlen+slen+1);
	return p;
}
