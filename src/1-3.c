#include "common.h"

const char * const USAGE = "Modify the temperature conversion program to print a heading above the table.\n\
Options:\n\
	./1-3 temp1 [, tempN] == Converts each arg to both Celsius and to Farenheit\n\
	./1-3 -c temp1 [, tempN] == Converts each arg to Celsius\n\
	./1-3 -f temp1 [, tempN] == Converts each arg to Farenheit\n";

float c2f(float c);
float f2c(float f);

int main (int argc, char ** argv)
{
	if(argc < 2)
	{
		fputs(USAGE,stdout);
		return 1;
	}

	int do_c2f = 0;
	int do_f2c = 0;
	int start_i = 1;
	if(strcmp(argv[1],"-c") == 0)
	{
		start_i++;
		do_c2f = 1;
	}
	else if(strcmp(argv[1],"-f") == 0)
	{
		start_i++;
		do_f2c = 1;
	}
	else
	{
		do_c2f = 
			do_f2c = 1;
	}
	for(int i = start_i; i < argc; i++)
	{
		if(do_c2f)
			printf("%s C == %0.4f F\n",argv[i],c2f(atof(argv[i])));
		if(do_f2c)
			printf("%s F == %0.4f C\n",argv[i],f2c(atof(argv[i])));
	}
	
	return 0;
}


float c2f(float c)
{
	return ((9.0/5.0) * c) + 32.0;
}

float f2c(float f)
{
	return (f - 32.0) * (5.0/9.0);
}
