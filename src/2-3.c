
#include <math.h>
#include "common.h"

const char * USAGE = "Write htoi which converts a char * of hex digits into an int number";


void impl( );
int htoi(char *);


int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
	char * hs[] = {
		"0X2A",
		"0x2A",
		"0x2a",
		"0x2",
		"0x1234567",
		"0x2f34b"
	};
	
	int i = 6;
	while( --i > -1 )
		printf("htoi %s = %d\n", hs[i],htoi(hs[i]));

}

int htoi(char * str)
{
	int retval = 0;
	if( strstr(str,"0X") != NULL || strstr(str,"0x") != NULL)
	{
		*++str;
		*++str;
	}
	int len = strlen(str);
	char * last_char = str + len - 1;
	
	char c;
	for(int j = 0; j < len; j++)
	{
		c = *last_char--;
		switch( c )
		{
			case 'A': case 'B': case 'C':
			case 'D': case 'E': case 'F':
				retval += pow(16,j) * ((c - 'A') + 10);
				break;
			case 'a': case 'b': case 'c':
			case 'd': case 'e': case 'f':
				retval += pow(16,j) * ((c - 'a') + 10 );
				break;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': 
				retval += pow(16,j) * ((c - '0'));
				break;
		}
	}

	return retval;
}

