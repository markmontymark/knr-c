#!/perl

use strict;
use warnings;

use Test::More;
use File::Which;
use File::Find;
use JSON::XS;
use File::Slurp;

my $test_cfg_file = shift;
my $test_dir = shift;
my $do_save = 0;

my $valgrind = File::Which::which('valgrind');
my $cfg = JSON::XS::decode_json( File::Slurp::read_file($test_cfg_file));

walk( $test_dir, \&run_tests );
done_testing();
#&save_cfg($cfg,$test_cfg_file) if $do_save;
exit;


sub run_tests
{
	my($path) = shift;
	my($name) = $path =~ m/\/+(.*?)$/;
	unless(exists $cfg->{$name})
	{
		print "Found test, $path, but $name doesn't exist in test config...Skipping\n";
		return;
	}
	
	my $test_cfg = $cfg->{$name};
	if($test_cfg && ref $test_cfg eq 'ARRAY')
	{
		&run_tests_on_cfg($_,$path) for @$test_cfg;
	}
	else
	{
		&run_tests_on_cfg($test_cfg,$path);
	}
}

sub run_tests_on_cfg
{
	my($test_cfg,$path) = @_;
	my $name = $test_cfg->{name};
	if(exists $test_cfg->{expected_file})
	{
		$test_cfg->{expected} = File::Slurp::read_file($test_cfg->{expected_file});
		#$do_save = 1;
	}

	unless(exists $test_cfg->{expected} or exists $test_cfg->{regex_expected})
	{
		print "Found test with $name but no 'expected' or 'regex_expected' is set...Skipping\n";
		return;
	}
	&basic_test($test_cfg,$path);
}

sub basic_test
{
	my($test_cfg,$path) = @_;
	return unless exists $test_cfg->{expected} or exists $test_cfg->{regex_expected};
	my $test_name = $test_cfg->{name};
	my $test_args = exists $test_cfg->{args} ? $test_cfg->{args} : undef;
	my $cmdline = $path;
	if(defined $test_args)
	{
		$test_args =~ s/^\s+//;
		$test_args =~ s/\s+$//;
		$cmdline .= " $test_args";
		$test_name .= " $test_args";
	}
	my $got = &trim(join '',`$cmdline`);
	if(exists $test_cfg->{regex_expected})
	{
		#&complain_about_unescaped_regex_modifiers($test_name,$test_cfg->{regex_expected});
		like($got, $test_cfg->{regex_expected} , $test_name);
		return;
	}

	my $r;
	## handle JSON not allowing multiline string literals by using array ref and joining with \n
	if( ($r = ref $test_cfg->{expected}) && $r eq 'ARRAY')
	{
		is($got, &trim(join "\n",@{$test_cfg->{expected}}) , $test_name );
	}
	else
	{
		is($got, &trim($test_cfg->{expected}) , $test_name);
	}
}

sub valgrind_test
{
	my($test_cfg,$cmdline) = @_;
	return unless defined $valgrind;
	return unless exists $test_cfg->{expected} or exists $test_cfg->{regex_expected};
	my $test_name = $test_cfg->{name} . ' Valgrind';
	my $got = &trim(join '',`$valgrind --leak-check=full $cmdline`);
	if(exists $test_cfg->{regex_expected})
	{
		like($got, $test_cfg->{regex_expected} , $test_name);
	}
	else
	{
		is($got, &trim($test_cfg->{expected}) , $test_name);
	}
}

sub complain_about_unescaped_regex_modifiers
{
	my($testname,$str) = @_;
	my($unwrapped_str) = $str;
	$unwrapped_str =~ s/^\///;
	$unwrapped_str =~ s/\/$//s;
	my @chars = split '',$unwrapped_str;
	my $i = -1;
	for(@chars)
	{
		$i++;
		next unless /[?\/*()+.]/;
		if( /[*+]/)
		{
			next if $i > 2 && ($chars[$i - 1] eq '\\' or $chars[$i-2] eq '\\' or $chars[$i-1] eq ']');
		}
		elsif( /[()]/)
		{
			next if $i > 2 && ($chars[$i - 1] eq '\\' or $chars[$i-2] eq '\\' or $chars[$i+1] eq '{');
		}
		else
		{
			next if $i > 1 && $chars[$i - 1] eq '\\';
		}
		print STDERR "xxxxx   test $testname has regex modifier $_ at pos $i\n";
	}
}

sub trim
{
	my $s = shift;
	$s =~ s/^\s+//;
	$s =~ s/\s+$//mg;
	$s
}

sub walk
{
	my($dir,$callback) = @_;
	$dir =~ s/\/$//; ## Remove trailing slash because we'll be adding one in `map` below
	opendir D,$dir || die "Can't opendir $dir, $!\n";
	my @entries = map{"$dir/$_"} grep !/^\./, readdir D;
	my @bins;
	my @dirs;
	for(@entries)
	{
		if( -d $_ )
		{
			push @dirs,$_;
		}
		elsif( -B $_ and -X $_ and (not -l $_) )
		{
			push @bins,$_;
		}
	}
	closedir D;
	$callback->($_) for sort {dictionary_sort($a,$b)} @bins;
	&walk($callback,$_) for sort @dirs;
}

sub save_cfg
{
   my($cfg,$path) = @_;
   my $coder = JSON::XS->new->ascii->pretty->allow_nonref;
   File::Slurp::write_file($path,$coder->encode($cfg));
}

sub dictionary_sort {
	my($a,$b) = @_;
	my($a_chap, $a_sct) = $a =~ m/\/(\d+)-(\d+)/;
	my($b_chap, $b_sct) = $b =~ m/\/(\d+)-(\d+)/;
	return -1 unless defined $a_chap && defined $a_sct;
	return  1 unless defined $b_chap && defined $b_sct;

	if($a_chap < $b_chap) {
		return -1;
	}
	elsif( $b_chap < $a_chap ) {
		return 1;
	}
	if( $a_sct < $b_sct ) {
		return -1;
	}
	elsif ( $b_sct < $a_sct ) {
		return 1;
	}
	return 0;
}
