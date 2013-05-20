#!/usr/bin/env perl

use strict;
use warnings;

use JSON::XS;
use File::Slurp;

my $test_cfg_file = shift; #
$test_cfg_file = 'test/ctest.json' unless defined $test_cfg_file;

my $cfg = JSON::XS::decode_json( File::Slurp::read_file($test_cfg_file));

&whats_not_done( $cfg );
exit;


sub whats_not_done
{
	my($cfg) = shift;
	for( sort keys %$cfg )
	{
		if(ref $cfg->{$_} eq 'ARRAY')
		{
			## for now, just test first testcase
			print "$_\n\t$cfg->{$_}->[0]->{expected}\n" unless 
				(exists $cfg->{$_}->[0]->{expected}  && $cfg->{$_}->[0]->{expected} =~ /\n/mg ) ||
				(exists $cfg->{$_}->[0]->{regex_expected}  && $cfg->{$_}->[0]->{regex_expected} =~ /(?:\\s|\n)/mg );
		}
		else
		{
			print "$_\n\t$cfg->{$_}->{expected}\n" unless 
				(exists $cfg->{$_}->{expected}  && $cfg->{$_}->{expected} =~ /\n/mg ) ||
				(exists $cfg->{$_}->{regex_expected}  && $cfg->{$_}->{regex_expected} =~ /(?:\\s|\n)/mg );
		}
	}	
}

