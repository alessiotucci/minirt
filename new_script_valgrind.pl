#!/usr/bin/perl

use strict;
use warnings;
use File::Basename;
use File::Compare;
use POSIX qw(strftime);
use Term::ANSIColor;
use IO::Select;

# Directory to store the log files
my $log_dir = 'debug_logs';
mkdir $log_dir unless -d $log_dir;

# Directory containing .rt files
my $dir = 'DIRmaps';
my @maps = glob "$dir/*.rt";

# Function to get the current date
sub get_current_date()
{
	return strftime "%d-%m_%W_%Y", localtime;
}

# Function to compare log files
sub compare_logs
{
    my ($new_log, $old_log) = @_;

    my $new_leaks = `grep "definitely lost" $new_log | awk '{print \$4}'`;
    my $old_leaks = `grep "definitely lost" $old_log | awk '{print \$4}'`;

    $new_leaks =~ s/,//g; # Remove commas
    $old_leaks =~ s/,//g; # Remove commas

    if ($new_leaks < $old_leaks)
	{
        print color('bold green');
        print "Leaks have decreased: $new_leaks bytes (new) vs $old_leaks bytes (old)\n";
    }
	elsif ($new_leaks > $old_leaks)
	{
        print color('bold red');
        print "Leaks have increased: $new_leaks bytes (new) vs $old_leaks bytes (old)\n";
    }
	else
	{
        print color('bold yellow');
        print "No change in leaks: $new_leaks bytes\n";
    }
    print color('reset');
}

# Function to prompt user for input with a 5-second timeout
sub prompt_user()
{
    print color('bold cyan');
    print "Enter map filename or 'TEST ALL' to test all maps (default: pt2.rt): ";
    print color('reset');

    my $input;
    my $s = IO::Select->new();
    $s->add(\*STDIN);

    if ($s->can_read(5)) {
        $input = <STDIN>;
        chomp $input;
    }
    $input ||= 'pt2.rt';
    return $input;
}

# Main script logic
my $input = prompt_user();

if ($input eq 'TEST ALL') {
    foreach my $map_file (@maps) {
        my $date = get_current_date();
        my $log_file = "$log_dir/" . basename($map_file, ".rt") . "_ALL_$date.txt";

        print color('bold blue');
        print "Running valgrind on $map_file\n";
        print color('reset');

        system("valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --verbose ./miniRT $map_file > $log_file 2>&1");

        # Compare with the most recent log file
        my @logs = glob "$log_dir/" . basename($map_file, ".rt") . "_ALL_*.txt";
        @logs = sort @logs;
        if (@logs > 1) {
            my $prev_log = $logs[-2];
            compare_logs($log_file, $prev_log);
        }
    }
} else {
    my $map_file = "$dir/$input";
    if (!-e $map_file) {
        print color('bold red');
        print "Error: The specified map file '$input' does not exist in the directory '$dir'.\n";
        print color('reset');
        exit 1;
    }
    my $date = get_current_date();
    my $log_file = "$log_dir/" . basename($map_file, ".rt") . "_$date.txt";

    print color('bold blue');
    print "Running valgrind on $map_file\n";
    print color('reset');

    system("valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --verbose ./miniRT $map_file > $log_file 2>&1");

    # Compare with the most recent log file
    my @logs = glob "$log_dir/" . basename($map_file, ".rt") . "_*.txt";
    @logs = sort @logs;
    if (@logs > 1) {
        my $prev_log = $logs[-2];
        compare_logs($log_file, $prev_log);
    }
}

# Help message
if (grep { $_ eq '-help' } @ARGV)
{
	print color('bold green');
	print "Usage: $0\n";
	print "This script runs valgrind on a specified .rt file in the DIRmaps directory.\n";
	print "The output is stored in the debug_logs directory with date-based naming.\n";
	print "If 'TEST ALL' is entered, the script runs valgrind on all .rt files in the directory.\n";
	print "After creating a new log file, the script compares it with the previous log file to check for changes in memory leaks.\n";
	print color('reset');
	exit;
}

