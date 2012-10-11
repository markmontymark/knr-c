  
#include "common.h"

const char * USAGE = "Write Celsius to Farenheit";

void impl( int argc, char ** argv );
float celsius2farenheit( float c);

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
		printf("%.2f C = %.2f F\n", temp, celsius2farenheit(temp));
	}
}

float celsius2farenheit( float c)
{
	return c * (9.0/5.0) + 32.0;
}
