package FindIncludes;

#
# analyse all .c and .h source files in a single directory, looking for
# #includes for files in the current directory (and assuming normal modular C
# comventions where X.c is the optional implementation half of X.h, not merely
# a coincidence in naming, and will necessarily #include "X.h").
# Generate a flattened list of dependencies, including indirect dependencies
# caused by nested includes (yes, I know, a tool I built is **finally**
# going to support nested includes cos I got fed up of explaining why they
# are not supported.  I hate nested includes personally but let's be nice
# to those who love nested includes too).
# 
# Written by Duncan C. White, June 2022, as a plugin replacement for the
# earlier direct-dependencies-only version that used to live in Rules.pm
#

use strict;
use warnings;
use feature 'say';
use Data::Dumper;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(
	find_all_direct_or_indirect_includes
	get_dirdeps
	);

my $debug = 0;

my %dirdeps;	# mapping from .c or .h filename to a set of all .h
		# files that it depends on DIRECTLY

#
# my %dirdeps = get_dirdeps();
#	Extract the direct dependencies, so that code
#	outside this module (eg graphing) can access them.
#
sub get_dirdeps ()
{
	return %dirdeps;
}


#
# find_all_direct_or_indirect_includes( \%cinc, \%h2c );
#	find all includes in all .c and .h files in the current directory,
#	initialising %cinc (a mapping from every c basename -> flattened list
#	of all (directly or indirectly) included .h basenames) and %h2c (a
#	set of basename.h for which there is a corresponding basename.c)
#
sub find_all_direct_or_indirect_includes
{
	my( $cincref, $h2cref ) = @_;

	my %deps;	# mapping from .c or .h filename to a set of all .h
			# files that it depends on (directly or indirectly)

	# populate %deps with all direct dependency information from #include
	# files in .c and .h files in the current directory
	foreach my $filename (glob("*.[ch]"))
	{
		open( my $infile, '<', $filename )
			|| die "cb: can't open $filename\n";
		while( <$infile> )
		{
			chomp;

			if( /^\s*#include\s+"(.+\.h)"/ )
			{
				next if $1 eq $filename;
				my $setref = ($deps{$filename} //= {});
				$setref->{$1}++;
				say "debug: $filename, found include $1"
					if $debug;
			}
		}
		close( $infile );
	}
	#die Dumper \%deps;

	# clone %deps into %dirdeps
	%dirdeps = ();
	map { $dirdeps{$_} = { %{$deps{$_}} } } keys %deps;
	#print Dumper \%dirdeps;
	#exit 0;

	# now, new code to flatten nested includes
	my %done;	# set of .h files we've already processed
	for(;;)
	{
		# locate all .h files including other .h files
		# (that we haven't already processed)
		my @hfiles = grep { /\.h$/ && ! $done{$_} } sort keys %deps;
	last unless @hfiles;

		#say "debug: processing h-including-h files: ".
		#	join( ',', @hfiles) if $debug;
		foreach my $ha (@hfiles)
		{
			my $bset = $deps{$ha};

			# $ha depends on all members of $bset

			# KEY STEP: locate all ($c, $dset) pairs where
			# $c is not $ha and $ha is in the $dset
			foreach my $c (keys %deps)
			{
				next if $c eq $ha;
				my $dset = $deps{$c};
				next unless $dset->{$ha};
				# found a pair as specified above
				# set union bset into dset (modifying dset)
				# EXCLUDING $c
				my $oldn = keys %$dset;
				map {
					$dset->{$_}++ unless $_ eq $c;
				} keys %$bset;
				my $newn = keys %$dset;

				# mark $c as "not done" if $dset grows
				# in order to look at $c again
				delete $done{$c} if $newn>$oldn;
			}
			$done{$ha}++;
		}
	}
	#die Dumper \%deps;

	# remove .h files from %deps
	delete $deps{$_} for grep { /\.h$/ } keys %deps;

	#die Dumper \%deps;

	# having removed all .h files from %deps, all keys are C files
	foreach my $cfile (keys %deps)
	{
		my $depref = $deps{$cfile};
		$cfile =~ s/\.c$//;
		my @includes = map { s/\.h$//; $_ } sort keys %$depref;
		$cincref->{$cfile} = [ @includes ];
		$h2cref->{$_} = -f "$_.c" ? 1 : 0     for @includes;
	}
	#die Dumper $cincref;
	#die Dumper $h2cref;
}


1;
