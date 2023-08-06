package OldFindIncludes;

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
	find_all_direct_includes
	);


my $debug = 0;

my $home = $ENV{HOME};


#
# find_all_direct_includes( \%cinc, \%h2c );
#	find all direct includes in all .c files in the current directory,
#	initialising %cinc (c basename -> list of included .h basenames)
#	and %h2c (a set of basename.h for which there is a corresponding
#	.c file)
#
sub find_all_direct_includes
{
	my( $cincref, $h2cref ) = @_;

	foreach my $filename (glob("*.c"))
	{
		my @includes;
		open( my $infile, '<', $filename ) || die "cb: can't open $filename\n";
		while( <$infile> )
		{
			chomp;

			if( /^\s*#include\s+"(.+).h"/ )
			{
				# append .h basename to include list
				push @includes, $1;
				#say "debug: $filename, found include $1";
			}
		}
		close( $infile );

		my $basename = $filename;
		$basename =~ s/\.c$//;
		$cincref->{$basename} = [ @includes ];
		$h2cref->{$_} = -f "$_.c" ? 1 : 0     for @includes;
	}
	#die Dumper $cincref;
	#die Dumper $h2cref;
}


1;
