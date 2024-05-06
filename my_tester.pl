#!/usr/bin/perl
use strict;
use warnings;
use File::Basename;
use Term::ANSIColor;

# Path to the miniRT executable
my $miniRT = './miniRT';

# Check if the miniRT executable exists
if (!-e $miniRT) {
    # If not, execute the make command
    system('make');
}

# Path to the WRONG directory
my $wrong_dir = './WRONG';

# Open the WRONG directory
opendir my $dh, $wrong_dir or die "Could not open '$wrong_dir' $!";

# Read all the files in the WRONG directory
while (my $map_file = readdir $dh)
{
    # Full path to the map file
    my $full_path = "$wrong_dir/$map_file";
    
    # Execute the miniRT application with the map file as a parameter
    my $output = `$miniRT $full_path 2>&1`;
    
    # Format the map file name
    my $formatted_map_file = basename($map_file, '.rt');  # Remove the .rt extension
    $formatted_map_file =~ s/_/ /g;  # Replace underscores with spaces
    
    # Print the output
    print "TESTIN OUT MAP: '$formatted_map_file':\n";
    if (defined $output)
	{
        print "$output\n";
    }
	else
	{
        print "No output from the command.\n";
    }
    print "---------------------------------\n";
}

closedir $dh;

