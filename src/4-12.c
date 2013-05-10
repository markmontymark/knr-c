
#include "common.h"

const char * USAGE = "Adapt printd, writing a recursive itoa";

void impl( );
void reverse(char * str);
int itoa(char ** dest,int num);

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	impl();
	return 0;
}

void impl( )
{
	char * a[0];
	itoa(a,12345);
	printf("itoa(12345) = %s, strlen %lu\n",*a,(unsigned long)strlen(*a));
	free(*a);

	itoa(a,1234);
	printf("itoa(1234) = %s, strlen %lu\n",*a,(unsigned long)strlen(*a));
	free(*a);

	itoa(a,123);
	printf("itoa(123) = %s, strlen %lu\n",*a,(unsigned long)strlen(*a));
	free(*a);

	itoa(a,12);
	printf("itoa(12) = %s, strlen %lu\n",*a,(unsigned long)strlen(*a));
	free(*a);

	itoa(a,1);
	printf("itoa(1) = %s, strlen %lu\n",*a,(unsigned long)strlen(*a));
	free(*a);

	itoa(a,1234567);
	printf("itoa(1234567) = %s, strlen %lu\n",*a,(unsigned long)strlen(*a));

	free(*a);
}

void reverse(char * str)
{
	if(str == NULL)
		return;

	int len = strlen(str);

	if(len < 2)
		return;

	char tmp;
	if( len == 2)
	{
		tmp = str[1];
		str[1] = str[0];
		str[0] = tmp;
		return;
	}

	int n_iters = len / 2;
	for(int i = 0; i < n_iters; i++)
	{
		tmp = str[--len];
		str[len] = str[i];
		str[i] = tmp;
	}
}

int itoa(char ** dest,int num)
{
	// figure out length of char * dest, so we malloc the right amount up front, 
	// then let _itoa fill dest with correct val
	int base = 10, len = 0;
	int realloc_size = 64;
	int is_neg = num < 0;

	if(num == 0)
	{
		char * a = malloc(sizeof(char *) * 2);
		a[0] = '0';
		a[1] = '\0';	
		*dest	= a;
		return 2;
	}

	char * a = malloc(realloc_size);
	char * tmp;
	int allocated = realloc_size;
	while(num)
	{
		if(len == allocated)
		{
			tmp = realloc(a,allocated + realloc_size);
			if(tmp == NULL)
			{
				free(a);
				return -1;
			}
			allocated += realloc_size;
			a = tmp;
		}
		a[len++] = '0' + (num%10);
		num /= 10;
	}
	if(len == allocated)
	{
		char * tmp = realloc(a,allocated + 1);
		if(tmp == NULL)
		{
			free(a);
			return -1;
		}
		allocated += 1;
		a = tmp;
		a[len++] = '0' + (num%10);
	}
	a[len] = '\0';
	tmp = realloc(a,len+1);
	if(tmp == NULL)
	{
		free(a);
		return -1;
	}
	*dest = tmp;
	reverse(*dest);

	return len;
}
