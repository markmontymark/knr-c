#include <stdio.h>
#include <unistd.h>


#ifdef _POSIX_ASYNCHRONOUS_IO
#define HAVE_AIO 1
#else
#define HAVE_AIO 0
#endif

int main( int argc, char ** argv )
{
	printf("have posix aio? %s\n", HAVE_AIO ? "yes":"no");
	return 0;
}
