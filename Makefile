B = bin
O = obj
#I = -Ilibmrk_include
L = -L./lib
#D = -lmrk

all: init $B/1-4 $B/1-16 $B/1-17 $B/1-18 $B/1-20 $B/1-21 $B/1-22 $B/1-23 $B/1-24 $B/1-24-stack $B/2-1 $B/2-3 $B/2-4 $B/2-6 $B/3-2 $B/3-3 $B/4-1 $B/4-2 $B/4-3 $B/4-12 $B/5-3 $B/5-4 $B/5-7 $B/5-9 $B/5-13 $B/5-17 $B/6-1 $B/6-3 $B/6-3-w-hashtable $B/6-5 $B/7-2 $B/7-3 $B/8-1 $B/8-3 $B/8-4 $B/8-5 $B/8-6 $B/8-7 $O/common.o

init: 
	mkdir -p $O $B

clean:
	rm -rf $O $B


$B/1-4: $O/1-4.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-4 $O/1-4.o $O/common.o

$O/1-4.o: src/1-4.c src/common.h
	gcc -std=gnu11 -g -c src/1-4.c -o $O/1-4.o

$B/1-16: $O/1-16.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-16 $O/1-16.o $O/common.o

$O/1-16.o: src/1-16.c src/common.h
	gcc -std=gnu11 -g -c src/1-16.c -o $O/1-16.o

$B/1-17: $O/1-17.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-17 $O/1-17.o $O/common.o

$O/1-17.o: src/1-17.c src/common.h
	gcc -std=gnu11 -g -c src/1-17.c -o $O/1-17.o


$B/1-18: $O/1-18.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-18 $O/1-18.o $O/common.o

$O/1-18.o: src/1-18.c src/common.h
	gcc -std=gnu11 -g -c src/1-18.c -o $O/1-18.o


$B/1-20: $O/1-20.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-20 $O/1-20.o $O/common.o

$O/1-20.o: src/1-20.c src/common.h
	gcc -std=gnu11 -g -c src/1-20.c -o $O/1-20.o


$B/1-21: $O/1-21.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-21 $O/1-21.o $O/common.o

$O/1-21.o: src/1-21.c src/common.h
	gcc -std=gnu11 -g -c src/1-21.c -o $O/1-21.o


$B/1-22: $O/1-22.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-22 $O/1-22.o $O/common.o

$O/1-22.o: src/1-22.c src/common.h
	gcc -std=gnu11 -g -c src/1-22.c -o $O/1-22.o


$B/1-23: $O/1-23.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-23 $O/1-23.o $O/common.o

$O/1-23.o: src/1-23.c src/common.h
	gcc -std=gnu11 -g -c src/1-23.c -o $O/1-23.o


$B/1-24: $O/1-24.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-24 $O/1-24.o $O/common.o

$O/1-24.o: src/1-24.c src/common.h
	gcc -std=gnu11 -g -c src/1-24.c -o $O/1-24.o

$B/1-24-stack: $O/1-24-stack.o $O/common.o
	gcc -std=gnu11 -g -o $B/1-24-stack $O/1-24-stack.o $O/common.o

$O/1-24-stack.o: src/1-24-stack.c src/common.h
	gcc -std=gnu11 -g -c src/1-24-stack.c -o $O/1-24-stack.o


$B/2-1: $O/2-1.o $O/common.o
	gcc -std=gnu11 -g -o $B/2-1 $O/2-1.o $O/common.o

$O/2-1.o: src/2-1.c src/common.h
	gcc -std=gnu11 -g -c src/2-1.c -o $O/2-1.o


$B/2-3: $O/2-3.o $O/common.o
	gcc -g -o $B/2-3 $O/2-3.o $O/common.o -lm -std=gnu11

$O/2-3.o: src/2-3.c src/common.h
	gcc -lm -std=gnu11 -g -c src/2-3.c -o $O/2-3.o


$B/2-4: $O/2-4.o $O/common.o
	gcc -std=gnu11 -g -o $B/2-4 $O/2-4.o $O/common.o

$O/2-4.o: src/2-4.c src/common.h
	gcc -std=gnu11 -g -c src/2-4.c -o $O/2-4.o


$B/2-6: $O/2-6.o $O/common.o
	gcc -std=gnu11 -g -o $B/2-6 $O/2-6.o $O/common.o

$O/2-6.o: src/2-6.c src/common.h
	gcc -std=gnu11 -g -c src/2-6.c -o $O/2-6.o


$B/3-2: $O/3-2.o $O/common.o
	gcc -std=gnu11 -g -o $B/3-2 $O/3-2.o $O/common.o

$O/3-2.o: src/3-2.c src/common.h
	gcc -std=gnu11 -g -c src/3-2.c -o $O/3-2.o


$B/3-3: $O/3-3.o $O/common.o
	gcc -std=gnu11 -g -o $B/3-3 $O/3-3.o $O/common.o

$O/3-3.o: src/3-3.c src/common.h
	gcc -std=gnu11 -g -c src/3-3.c -o $O/3-3.o


$B/4-1: $O/4-1.o $O/common.o
	gcc -std=gnu11 -g -o $B/4-1 $O/4-1.o $O/common.o

$O/4-1.o: src/4-1.c src/common.h
	gcc -std=gnu11 -g -c src/4-1.c -o $O/4-1.o


$B/4-2: $O/4-2.o $O/common.o
	gcc -std=gnu11 -g -o $B/4-2 $O/4-2.o $O/common.o

$O/4-2.o: src/4-2.c src/common.h
	gcc -std=gnu11 -g -c src/4-2.c -o $O/4-2.o


$B/4-3: $O/4-3.o $O/common.o
	gcc -std=gnu11 -g -o $B/4-3 $O/4-3.o $O/common.o

$O/4-3.o: src/4-3.c src/common.h
	gcc -std=gnu11 -g -c src/4-3.c -o $O/4-3.o


$B/4-12: $O/4-12.o $O/common.o
	gcc -std=gnu11 -g -o $B/4-12 $O/4-12.o $O/common.o

$O/4-12.o: src/4-12.c src/common.h
	gcc -std=gnu11 -g -c src/4-12.c -o $O/4-12.o


$B/5-3: $O/5-3.o $O/common.o
	gcc -std=gnu11 -g -o $B/5-3 $O/5-3.o $O/common.o -Wall

$O/5-3.o: src/5-3.c src/common.h
	gcc -std=gnu11 -g -c src/5-3.c -o $O/5-3.o

$B/5-4: $O/5-4.o $O/common.o
	gcc -std=gnu11 -g -o $B/5-4 $O/5-4.o $O/common.o

$O/5-4.o: src/5-4.c src/common.h
	gcc -std=gnu11 -g -c src/5-4.c -o $O/5-4.o


$B/5-7: $O/5-7.o $O/common.o
	gcc -std=gnu11 -g -o $B/5-7 $O/5-7.o $O/common.o

$O/5-7.o: src/5-7.c src/common.h
	gcc -std=gnu11 -g -c src/5-7.c -o $O/5-7.o


$B/5-9: $O/5-9.o $O/common.o
	gcc -std=gnu11 -g -o $B/5-9 $O/5-9.o $O/common.o

$O/5-9.o: src/5-9.c src/common.h
	gcc -std=gnu11 -g -c src/5-9.c -o $O/5-9.o


$B/5-13: $O/5-13.o $O/common.o
	gcc -std=gnu11 -g -o $B/5-13 $O/5-13.o $O/common.o

$O/5-13.o: src/5-13.c src/common.h
	gcc -std=gnu11 -g -c src/5-13.c -o $O/5-13.o


$B/5-17: $O/5-17.o $O/common.o
	gcc -std=gnu11 -g -o $B/5-17 $O/5-17.o $O/common.o

$O/5-17.o: src/5-17.c src/common.h
	gcc -std=gnu11 -g -c src/5-17.c -o $O/5-17.o


$B/6-1: $O/6-1.o $O/common.o
	gcc -std=gnu11 -g -o $B/6-1 $O/6-1.o $O/common.o

$O/6-1.o: src/6-1.c src/common.h
	gcc -std=gnu11 -g -c src/6-1.c -o $O/6-1.o


$B/6-3: $O/6-3.o $O/common.o
	gcc $I -std=gnu11 -g -o $B/6-3 $O/6-3.o $O/common.o $L $D

$O/6-3.o: src/6-3.c src/common.h
	gcc $I -std=gnu11 -g -c src/6-3.c -o $O/6-3.o

$B/6-3-w-hashtable: $O/6-3-w-hashtable.o $O/common.o 
	gcc $I -std=gnu11 -g -o $B/6-3-w-hashtable $O/6-3-w-hashtable.o $O/common.o $L $D

$O/6-3-w-hashtable.o: src/6-3-w-hashtable.c src/common.h
	gcc $I -std=gnu11 -g -c src/6-3-w-hashtable.c -o $O/6-3-w-hashtable.o

$B/6-5: $O/6-5.o $O/common.o
	gcc $I -std=gnu11 -g -o $B/6-5 $O/6-5.o $O/common.o $L $D

$O/6-5.o: src/6-5.c src/common.h
	gcc $I -std=gnu11 -g -c src/6-5.c -o $O/6-5.o


$B/7-2: $O/7-2.o $O/common.o
	gcc -std=gnu11 -g -o $B/7-2 $O/7-2.o $O/common.o

$O/7-2.o: src/7-2.c src/common.h
	gcc -std=gnu11 -g -c src/7-2.c -o $O/7-2.o


$B/7-3: $O/7-3.o $O/common.o
	gcc -std=gnu11 -g -o $B/7-3 $O/7-3.o $O/common.o

$O/7-3.o: src/7-3.c src/common.h
	gcc -std=gnu11 -g -c src/7-3.c -o $O/7-3.o


$B/8-1: $O/8-1.o $O/common.o
	gcc -std=gnu11 -g -o $B/8-1 $O/8-1.o $O/common.o

$O/8-1.o: src/8-1.c src/common.h
	gcc -std=gnu11 -g -c src/8-1.c -o $O/8-1.o


$B/8-3: $O/8-3.o $O/common.o
	gcc -std=gnu11 -g -o $B/8-3 $O/8-3.o $O/common.o

$O/8-3.o: src/8-3.c src/common.h
	gcc -std=gnu11 -g -c src/8-3.c -o $O/8-3.o


$B/8-4: $O/8-4.o $O/common.o
	gcc -std=gnu11 -g -o $B/8-4 $O/8-4.o $O/common.o

$O/8-4.o: src/8-4.c src/common.h
	gcc -std=gnu11 -g -c src/8-4.c -o $O/8-4.o


$B/8-5: $O/8-5.o $O/common.o
	gcc -std=gnu11 -g -o $B/8-5 $O/8-5.o $O/common.o

$O/8-5.o: src/8-5.c src/common.h
	gcc -std=gnu11 -g -c src/8-5.c -o $O/8-5.o


$B/8-6: $O/8-6.o $O/common.o
	gcc -std=gnu11 -g -o $B/8-6 $O/8-6.o $O/common.o

$O/8-6.o: src/8-6.c src/common.h
	gcc -std=gnu11 -g -c src/8-6.c -o $O/8-6.o


$B/8-7: $O/8-7.o $O/common.o
	gcc -std=gnu11 -g -o $B/8-7 $O/8-7.o $O/common.o

$O/8-7.o: src/8-7.c src/common.h
	gcc -std=gnu11 -g -c src/8-7.c -o $O/8-7.o

$O/common.o: src/common.h src/common.c
	gcc -std=gnu11 -g -c src/common.c -o $O/common.o


##
## Creating libraries
##

# Create static library
#
# compile (create $Oect, .o, files  from impl, .c, files)
# gcc -c calc_mean.c -o calc_mean.o
# Then, the archiver (ar) is invoked to produce a static library (named libmean.a) out of the $Oect file calc_mean.o.
# ar  rcs libmean.a      calc_mean.o

# Create shared library
# compile - creating $Oect, .o, files from impl, .c, files
# gcc -c -fPIC file1.c -o file1.o
# gcc -c -fPIC ...c -o ...o
# gcc -c -fPIC fileN.c -o fileN.o
# gcc -shared -Wl,-soname,libmean.so.1 -o libmean.so.1.0.1  file1.o ...o fileN.o


##
## Using libraries
##

# Linking against static library
#
# Note: the first three letters (the lib) must not be specified, as well as the suffix (.a)
# gcc -static main.c -L. -lmean -o statically_linked

# Linking against shared library
#
# Note: the first three letters (the lib) must not be specified, as well as the suffix (.so)
# gcc main.c -o dynamically_linked -L. -lmean

##
## Executing dynamically linked program (no steps needed for statically linked
##

# Executing the dynamically linked programm
# LD_LIBRARY_PATH=.
# ./dynamically_linked

