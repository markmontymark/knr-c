#!/usr/bin/perl

use strict;
use warnings;

&usage unless -e 'README';
&make_project_files();
exit;

sub make_project_files
{
	open T,'tmpl.c' || die "Can't read tmpl.c, $!\n";
	my $c_tmpl = join '',<T>;
	close T;

	open T,'Makefile.tmpl' || die "Can't read Makefile.tmpl, $!\n";
	my $m_tmpl = join '',<T>;
	close T;

	open F,'README' || die "Can't read README, $!\n";
	my $prog;
	my @progs;
	my @lines;
	while(<F>)
	{
		if(/^(\d+-\d+)/)
		{
			$prog = $1;
			@lines = ();
		}
		elsif(/^\s*$/)
		{
			if($prog)
			{
				push @progs,[$prog,[@lines]];
			}
			$prog = undef;
			@lines = ();
		}
		elsif(defined $prog)
		{
			push @lines,$_;
		}
	}

	&create_file('Makefile','
SRCDIR = src
BUILDDIR = build
DISTDIR = dist
COMPILE_C_CMD = gcc -O0 -g3 -Wall -fmessage-length=0 -std=gnu11
INCLUDES = 
LIBS = 

all:
	mkdir -p $(BUILDDIR)
	mkdir -p $(DISTDIR) ' . join('',map{"
	\$(COMPILE_C_CMD) \$(INCLUDES) \$(LIBS) -o \$(BUILDDIR)/$_->[0].o  \$(SRCDIR)/$_->[0].c
	cp \$(BUILDDIR)/$_->[0].o \$(DISTDIR)/$_->[0]"}@progs) .'

clean:
	rm -rf $(BUILDDIR)
	rm -rf $(DISTDIR)
');
	&create_file('Makefile.new',''.
	join("\n",map{
		my $t = $m_tmpl;
		$t =~ s/__FILE__/$_->[0]/isg;
		$t
	}@progs) .'

obj/common.o: src/common.h src/common.c
	gcc -std=gnu11 -g -c src/common.c -o obj/common.o
');


	for my $proj (@progs)
	{
		my($project_name,$project_comment) = @$proj;
		my @lines = @$project_comment;

		if( -e "src/$project_name.c")
		{
			print "src/$project_name.c exists, skipping\n";
			next;
		}	
	
		chomp @lines;
		for(@lines)
		{
			s/^\s+//;
			s/\s+$//;
		}
		my $c_code = $c_tmpl;
		$c_code =~ s/__COMMENT__/join(' ',@lines)/esg;
		
		&create_file("src/$project_name.c",$c_code);
	}



}

sub create_file
{
	my($filename,$content) = @_;
	open N ,">$filename" || die "Can't create flie $filename, $!\n";
	print N $content;
	close N;
}

sub usage
{
	print STDERR "Error, you need to pass a project name\nUsage $0 <project_name>\n";
	exit(1);
}

