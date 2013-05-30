#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

const char * USAGE = "Design and write _flushbuf(), fflush(), fclose()\n";

#undef NULL
#undef stdin
#undef stdout
#undef stderr


#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20
#define PERMS 0666

typedef struct _iobuf{
	int cnt; 		// characters left
	char * ptr; 	// next character position
	char * base;	// location of buffer
	int flag;		// mode of file access
	int fd;			// file descriptor
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
	_READ = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF	= 010,
	_ERR	= 020
};
FILE _iob[OPEN_MAX] = {
	{ 0, (char *)0, (char *)0, _READ, 0 },
	{ 0, (char *)0, (char *)0, _WRITE, 1 },
	{ 0, (char *)0, (char *)0, _WRITE | _UNBUF, 2 }
};

int _makebuf( FILE * );
int _fillbuf( FILE * );
int _flushbuf( int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar() getc(stdin)
#define putchar(x) putc((x),stdout)

int _makebuf( FILE * fp )
{
	if( fp == NULL )
		return -1;

	if( fp->base != NULL)
		return fp->cnt;
	
	int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	
	if (( fp->base = (char *)malloc(bufsize)) == NULL)
	{
		//write(stderr->fd, "_malloc ret       is  nul\n" ,26);
		return -1; // such silent nasty errors
	}
	fp->ptr = fp->base;
	fp->cnt = 0;
	return bufsize;
}


int _fillbuf( FILE * fp )
{
	int bufsize;
	
	if((fp->flag & (_READ|_WRITE|_EOF|_ERR)) != _READ)
		return EOF;
	
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	//write(stdout->fd, "bufsize\n",9);
	//write(stdout->fd, bufsize,5);
	//write(stdout->fd, "\n",2);

	_makebuf(fp);	

	fp->cnt = read( fp->fd, fp->ptr, bufsize );
	if( --fp->cnt < 0 )
	{
		fp->flag |= (fp->cnt == -1) ? _EOF : _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}


int _flushbuf( int c, FILE * fp)
{
	int bufsize;
	
	if((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
		return EOF;
	
	if( fp->flag & _UNBUF)
	{
		//write(stdout->fd, "_flushbuf bufsize is one\n" ,25);
		if( write(fp->fd, &c, 1) == -1 )
			;
		return EOF;
	}

	// nothing to do yet, nothing to flush, so just fill with char c	
	if( fp->base == NULL)
	{
		if( c == EOF )
			return EOF;
		_makebuf(fp);
		*fp->ptr++ = c;
		return 0;
	}
	// buffer to flush, then add char c, unless c is EOF, then just return EOF
	int toWrite = fp->ptr - fp->base;
	int nwrote = write(fp->fd, fp->base, toWrite);
	if( c == EOF)
		return EOF;
	fp->ptr = fp->base;
	fp->cnt = BUFSIZ - 1;
	*(fp)->ptr++ = c;
	return nwrote;	
}

FILE * fopen( char * name, char * mode)
{
	int fd;	
	FILE * fp;

	if( *mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for( fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if( (fp->flag & (_READ | _WRITE)) == 0 )
			break; // found free slot

	if( fp >= _iob + OPEN_MAX)
		return NULL; // nasty silent error

	if(*mode == 'r')
	{
		fd = open(name, O_RDONLY, 0);
	}
	else if( *mode == 'w' )
	{
		fd = creat(name, PERMS);
	}
	else if( *mode =='a')
	{
		if((fd = open(name,O_WRONLY,0)) == -1)
			fd = creat(name,PERMS);
		lseek(fd,0L,2);
	}
	if(fd == -1)
		return NULL;//another nasty silent error, or at least set errno to something nice
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ :_WRITE;
	return fp;
}

int fflush(FILE * fp)
{
	//write(stderr->fd, "fflush fp\n" ,11);
	_flushbuf(EOF,fp);	
}


int fclose(FILE * fp)
{
	if( fp == NULL )
		return 0;
	if(fp->cnt > 0)
		fflush(fp);
	int closeRetval = close(fp->fd);
	return closeRetval;
}

int main( int argc, char ** argv )
{
	//if( (write(stdout->fd,USAGE,strlen(USAGE)+1)) == -1)
		//return -1;

	char * test_data_file = "/tmp/asdfasdfasdfadsf";
	char * test_str = "Hello World\n";
	FILE * f;

	if( (f = fopen(test_data_file,"w")) == NULL )
	{
		char * msg = "Error opening test_data_file for write-only\n";
		if( (write(stderr->fd,msg,strlen(msg)+1) ) == -1)
			return -1;
	}

	for( int i = 0; i < 1025; i++)
		for( char * j = test_str; *j; j++)
			putc( *j,f);
	fclose(f);

	if( (f = fopen( test_data_file,"r")) == NULL )
	{
		char * msg = "Error opening test_data_file for read-only\n";
		if( (write(stderr->fd,msg,strlen(msg)+1) ) == -1)
			return -1;
	}
	char c;
	while( (c = getc(f)) != EOF )
		if( write( stdout->fd, &c, 1) == -1 )
			;
	fclose(f);

	if( unlink( test_data_file) )
	{
	}

	return 0;
}

