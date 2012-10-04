  
#include "common.h"

const char * USAGE = "Write Celsius to Farenheit";

void impl( int argc, char ** argv );
float c2f( float c);

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl(argc,argv);
	return 0;
}

void impl( int argc, char ** argv)
{
	float temp;
	for(int i = 1; i < argc; i++)
	{
		temp = atof(argv[i]);
		printf("%.2f C = %.2f F\n", temp, c2f(temp));
	}
}

float c2f( float c)
{
	return c * ((float)9/5) + 32;
}
