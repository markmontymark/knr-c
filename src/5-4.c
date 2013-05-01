
#include "common.h"

const char * USAGE = "Write strend (better called endsWith(str,substr)) that returns 1 if str ends with substr";

void impl( );

int endsWith(const char * s, const char * substr);
int test_endsWith(const char * s, const char * substr,int expectedResult);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
	const char * src = "This is a sentence";
	const char * substr1 = "ence";
	const char * substr2 = "sentence";

	test_endsWith( src, substr1, 1 );
	test_endsWith( src, "wrong", 0 );
	test_endsWith( src, substr2, 1 );
	test_endsWith( "", ".", 0 );
	test_endsWith( "", "", 1 );
	test_endsWith( NULL, NULL, 0 );
	test_endsWith( "a", "a", 1 );
	
}

int test_endsWith(const char * s, const char * substr,int expectedResult)
{
	printf("%s endsWith %s? ", s,substr);
	int result = endsWith(s,substr);
	printf("%s,  %s\n", result ? "yes" : "no", result == expectedResult ? "passed":"failed");
	
}

int endsWith(const char * s, const char * substr)
{
	if( s == NULL || substr == NULL)
		return 0;

	int sublen = strlen(substr);
	int slen = strlen(s);
	if(sublen > slen)
		return 0;

	s += slen - sublen;
	return strcmp(s,substr) == 0;
}
