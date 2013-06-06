const char * USAGE = "Suppose that there will never be more than one char of pushback, Modify getch and ungetch accordingly";

#include "stdio.h"

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch()
{
	return  (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int buf_onechar = EOF;
int getch_onechar()
{
	if(buf_onechar == EOF) 
		return getchar();
	int c = buf_onechar;
	buf_onechar = EOF;
	return c;
}
void ungetch_onechar(int c)
{
	if(buf_onechar != EOF)
		printf("ungetch_onechar: too many characters\n");
	else
		buf_onechar = c;
}

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	int c;
	while( (c = getch_onechar()) != EOF)
		printf("%c",c);
	return 0;
}

