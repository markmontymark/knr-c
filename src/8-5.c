
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include "common.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "time.h"
#include "unistd.h"

const char * USAGE = "modify fsize to print all info contained in inode entries";

void impl( );

int main( int argc, char ** argv )
{
	printf("%s\n",USAGE);
	while(--argc > 0)
		impl(*++argv);
	return 0;
}

void impl( char * path )
{
/*
	struct stat {
		dev_t     st_dev;     // ID of device containing file
		ino_t     st_ino;     // inode number
		mode_t    st_mode;    // protection
		nlink_t   st_nlink;   // number of hard links
		uid_t     st_uid;     // user ID of owner
		gid_t     st_gid;     // group ID of owner
		dev_t     st_rdev;    // device ID (if special file)
		off_t     st_size;    // total size, in bytes
		blksize_t st_blksize; // blocksize for file system I/O
		blkcnt_t  st_blocks;  // number of 512B blocks allocated
		time_t    st_atime;   // time of last access 
		time_t    st_mtime;   // time of last modification 
		time_t    st_ctime;   // time of last status change
	};
*/
	struct stat st;
	stat( path, &st);	
	printf("Stat %s: \n"
		"\tdev_t: %d\n"
		"\tino_t: %ld\n"
		"\tmode_t: %d\n"
		"\tnlink_t: %d\n"
		"\tuid_t: %d\n"
		"\tgid_t: %d\n"
		"\tdev_t: %d\n"
		"\toff_t: %d\n"
		"\tblksize_t: %d\n"
		"\tblkcnt_t: %d\n"
		"\ttime_t: %d\n"
		"\ttime_t: %d\n"
		"\ttime_t: %d\n",
		path,
		(int)st.st_dev,
		(long)st.st_ino,
		st.st_mode,
		(int)st.st_nlink,
		st.st_uid,
		st.st_gid,
		(int)st.st_rdev,
		(int)st.st_size,
		(int)st.st_blksize,
		(int)st.st_blocks,
		(int)st.st_atime,
		(int)st.st_mtime,
		(int)st.st_ctime
	);
	
}

