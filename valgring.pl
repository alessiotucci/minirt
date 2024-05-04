#!/usr/bin/perl

use strict;
use warnings;

my $dir = 'DIRmaps';
my @maps = glob "$dir/*.rt";

foreach my $map_file (@maps)
{
	print "Running valgrind on $map_file\n";
system("valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --verbose  ./miniRT $map_file");
}


