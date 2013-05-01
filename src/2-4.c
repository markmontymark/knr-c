
#include "common.h"

const char * USAGE = "Write a function, squeeze(char *  srcString,char * subString) that deletes all occurences of each char in subString in srcString";

void impl( );
void squeeze(char * str,char * substr);
void popString(char * str,int indexToRemove);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
	char str[] = "Start with a longish string";
	char * substr1 = "s";
	char * substr2 = "h";
	char * substr3 = "e";

	printf("Original string: %s\n",str);	
	squeeze(str,substr1);
	printf("Result after squeeze with %s: %s\n",substr1,str);	
	squeeze(str,substr2);
	printf("Result after squeeze with %s: %s\n",substr2,str);	
	squeeze(str,substr3);
	printf("Result after squeeze with %s: %s\n",substr3,str);	
}

void squeeze(char * str,char * charsToRemove)
{
	char ci;
	int found;
	int i,j;
	char * tmpCharsToRemove;

	for(i=j=0; str[i]; i++)
	{
		ci = str[i];
		found = 0;
		tmpCharsToRemove = charsToRemove;
		while(*tmpCharsToRemove)
		{
			if( ci == *tmpCharsToRemove++)
			{
				found = 1;
				break;
			}
		}
		if( ! found )
			str[j++] = str[i];
	}
	str[j] = '\0';
}
