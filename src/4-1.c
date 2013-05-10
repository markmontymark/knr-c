#include <stdio.h>
#include <string.h>

const char * USAGE = "Write a strrindex(s,t) function that return the last occurrence of t in s or -1 if not found (this can be compared to rindex?)";

int strrindex(const char * s,char t);
int test_strrindex(const char * s,char t);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	char * str = "This is a string we will test the last index for.";
	test_strrindex(str,'t');
	test_strrindex(str,'z');
	test_strrindex(str,'r');

	test_strrindex("r",'r');
	test_strrindex("",'z');
	return 0;
}

int test_strrindex(const char *s,char t)
{
	printf("Last index of %c in %s is ",t,s);
	int retval = strrindex(s,t);
	printf("%d\n",retval);
	return 0;
}

int strrindex(const char * s,char t)
{
	int len = strlen(s);
	while(--len > -1)
		if(s[len] == t)
			return len;
	return len;
}

