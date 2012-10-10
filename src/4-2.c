
#include "math.h"
#include "common.h"

const char * USAGE = "Write an atof function that handles scientific notation";

struct significand_num
{
	int length;
	int digits[256];
};

typedef struct scinot scinot_t;
struct scinot
{
	int significand_sign; // -1 or 1
	int exponent_sign; // -1 or 1
	long significand; // nums to left of decimal
	long fractional; // nums to left of decimal
	double exponent; // nums to right of decimal
};

enum parse_scinot_states
{
	SIGNIFICAND,
	FRACTION,
	EXPONENT
};

void impl( );
double scientific_notation_to_double(char * str);

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl();
	return 0;
}

void impl( )
{
	char * nums[7];
	nums[0] = "1";
	nums[1] = "12";
	nums[2] = "1.2";
	nums[3] = ".1";
	nums[4] = ".12";
	nums[5] = "0.1";
	nums[6] = "0.12";

	char * es[6];
	es[0] = "e";
	es[1] = "E";
	es[2] = "-e";
	es[3] = "+e";
	es[4] = "-E";
	es[5] = "+E";

	char * exps[3];
	exps[0] = "1";
	exps[1] = "12";
	exps[2] = "0";

	char * str = malloc( 80 );
	for(int i = 0; i < 7; i++)
	{
		for(int j = 0; j < /*6*/6; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				snprintf(str,
					80,
					"%s%s%s",nums[i],es[j],exps[k] );
				printf("local_atof(%s) = %f\n\n\n\n", str, scientific_notation_to_double(str)); 
			}
		}
	}

}

double scientific_notation_to_double(char * str)
{
	char * str_tmp = str;
	int state = SIGNIFICAND;
	char c;
	int cnum = 0;
	scinot_t retval = {1,1,0,0,0};
	struct significand_num sg;
	sg.length = 0;
	struct significand_num frac;
	frac.length = 0;
	struct significand_num exp;
	exp.length = 0;
	printf("starrt %s\n",str);
	while( (c = *str++))
	{
		cnum++;
		switch(state)
		{
			case SIGNIFICAND:
				if( c == '-')
					if( sg.length == 0)
						retval.significand_sign = -1;
					else
					{
						retval.exponent_sign = -1;
						state = EXPONENT;
					}

				else if( c == '+')
					if( sg.length == 0)
						retval.significand_sign = 1;
					else
					{
						retval.exponent_sign = 1;
						state = EXPONENT;
					}

				else if(c == 'E' || c == 'e')
				{
					state = EXPONENT;
					break;
				}

				else if( c == '.' )
				{
					state = FRACTION;	
				}
				else if( isdigit(c) )
					sg.digits[sg.length++] = (int)c-(int)'0';

				else
					printf("parse error at character %c, position %d, string %s\n",c,cnum,str_tmp);

				break;

			case FRACTION:
				if( isdigit(c) )
					frac.digits[ frac.length++ ] = (int)c-(int)'0';

				else if( c == '-' )
				{
					state = EXPONENT;
					retval.exponent_sign = -1;
				}

				else if( c == '+')
				{
					state = EXPONENT;
					retval.exponent_sign = 1;
				}

				else if(c == 'E' || c == 'e')
				{
					state = EXPONENT;
					break;
				}
				else
					printf("parse error at character %c, position %d, string %s\n",c,cnum,str_tmp);
				break;

			case EXPONENT:
				if( isdigit(c) )
					exp.digits[ exp.length++ ] = (int)c-(int)'0';
				else
					printf("parse error at character %c, position %d, string %s\n",c,cnum,str_tmp);
				break;
		}
	}

	int power = 0;
	long sum = 0;
	while( --sg.length  > -1 )
	{
		sum += pow(10,power++) * sg.digits[ sg.length ];
		printf("building sig.digits[%d] = %d, sum %ld\n",sg.length,sg.digits[sg.length],sum);
	}
	printf("sig final %ld\n",sum );
	retval.significand = sum;

	power = 0;
	sum = 0;
	long divisor = 1;
	while( --frac.length  > -1 )
	{
		divisor *= 10;
		sum += pow(10,power++) * frac.digits[ frac.length ];
		printf("building frac.digits[%d] = %d, sum %ld\n",frac.length,frac.digits[frac.length],sum);
	}
	printf("frac final %ld\n",sum );
	retval.fractional = sum;


	power = 0;
	sum = 0;
	while( --exp.length  > -1 )
	{
		sum += pow(10,power++) * exp.digits[ exp.length ];
		printf("building exp.digits[%d] = %d, sum %ld\n",exp.length,exp.digits[exp.length],sum);
	}
	if(retval.exponent_sign == -1)
		if(sum == 0)
			retval.exponent = 1;
		else
			retval.exponent = 1/sum;
	else
		retval.exponent = sum;
	printf("exp final %.9f\n",retval.exponent);

	printf("%s parts %c%ld.%ld%c%.9f\n", str_tmp,retval.significand_sign == 1 ? '+' : '-' ,retval.significand, retval.fractional, retval.exponent_sign==1?'+':'-', retval.exponent);

	return retval.significand * retval.exponent;//1.0;
}

