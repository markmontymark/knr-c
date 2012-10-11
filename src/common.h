#ifndef __COMMON_H_
#define __COMMON_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

int can_open_data_file(const char * progname);
void usage(const char * usage_msg, const char * prog_name);
void get_progname(char * path);
void get_rcfile(char * dest,const char * progname);
int open_data_file(const char * progname,FILE * fp);
int read_line(char ** dest, int realloc_size, FILE *fp) ;

#endif
