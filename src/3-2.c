
const char * USAGE = "Write escape(to,from) which converts newline to \n and tab to \t";

void impl( );
void escape(char * from,char * to);

int main( int argc, char ** argv )
{
	char * from = "This is a sentence with a literal newline -\n- and a literal -\t-.";
	char * to = malloc(strlen(from)+1);
	escape(from,to);
	printf("from: %s\nto  : %s\n",from,to);
	free(to);

	char * from2 = "T\n\n\n\n\n\n\n\n\nhis is a sentence \t\t\t\twith a literal newline -\n- and a literal -\t-.";
	char * to2 = malloc(strlen(from2) + 1);
	escape(from2,to2);
	printf("from: %s\nto  : %s\n",from2,to2);
	return 0;
}

void escape(char * from,char * to)
{
	while( *from )
	{
		if( *from == '\n')
		{
			*to = '\\';
			*++to = 'n';
			*to++;
		}
		else if( *from == '\t')
		{
			*to = '\\';
			*++to = 't';
			*to++;
		}
		else
		{
			*to++ = *from;
		}	
		from++;
	}
}
