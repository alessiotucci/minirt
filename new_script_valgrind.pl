#!/usr/bin/perl

use strict;
use warnings;
use File::Basename;
use POSIX qw(strftime);
use Term::ANSIColor;

# Configuration
my $MAPS_DIR = 'DIRmaps';
my $LOG_DIR = 'debug_logs';
my $DEFAULT_MAP = 'pt2.rt';
my $EXECUTABLE = './miniRT';

# Setup directories
mkdir $LOG_DIR unless -d $LOG_DIR;

sub get_timestamp
{
    return strftime("%Y-%m-%d %H:%M:%S", localtime);
}

sub print_header
{
    my ($message) = @_;
    print color('bold cyan');
    print "\n" . '=' x 50 . "\n";
    print "$message\n";
    print '=' x 50 . "\n\n";
    print color('reset');
}

sub get_leak_info
{
    my ($log_file) = @_;
    return 0 unless -e $log_file;

    open my $fh, '<', $log_file or return 0;
    while (my $line = <$fh>)
    {
        if ($line =~ /definitely lost:\s+([\d,]+)\s+bytes/)
        {
            my $leaks = $1;
            $leaks =~ s/,//g;
            close $fh;
            return $leaks + 0;
        }
    }
    close $fh;
    return 0;
}

sub run_valgrind
{
    my ($map_path) = @_;
    my $map_name = basename($map_path);
    my $timestamp = get_timestamp();
    my $log_file = "$LOG_DIR/${map_name}_${timestamp}.log";

    print_header("TESTING MAP: $map_name");

    my $cmd = "valgrind --tool=memcheck --leak-check=full " .
              "--show-leak-kinds=all --track-origins=yes " .
              "$EXECUTABLE '$map_path' > '$log_file' 2>&1";

    print color('yellow');
    print "Running: $cmd\n\n";
    system($cmd);

    return $log_file;
}

sub find_previous_log
{
    my ($current_log) = @_;
    my $pattern = $current_log;
    $pattern =~ s/_\d{4}-\d{2}-\d{2}.*\.log$//;
    $pattern .= "_*.log";

    my @logs = sort glob($pattern);
    return unless @logs >= 2;
    return $logs[-2];
}

sub report_leaks
{
    my ($log_file) = @_;
    my $current_leaks = get_leak_info($log_file);
    my $previous_log = find_previous_log($log_file);
    my $previous_leaks = $previous_log ? get_leak_info($previous_log) : 0;

    print_header("MEMORY LEAK REPORT");

    print color('bold white');
    printf "%-30s: %s\n", "Current test", basename($log_file);
    printf "%-30s: %s\n", "Current leaks", $current_leaks;

    if ($previous_log)
    {
        printf "%-30s: %s\n", "Previous test", basename($previous_log);
        printf "%-30s: %s\n", "Previous leaks", $previous_leaks;

        print "\n";
        if ($current_leaks < $previous_leaks)
        {
            print color('bold green');
            printf "IMPROVEMENT: -%d bytes\n", ($previous_leaks - $current_leaks);
        }
        elsif ($current_leaks > $previous_leaks)
        {
            print color('bold red');
            printf "REGRESSION: +%d bytes\n", ($current_leaks - $previous_leaks);
        }
        else
        {
            print color('bold yellow');
            print "NO CHANGE\n";
        }
    }
    else
    {
        print color('bold cyan');
        print "\nNo previous logs found for comparison\n";
    }

    print color('reset');
    print "\n" . '-' x 50 . "\n\n";
}

sub select_map
{
    print color('bold green');
    print "Available maps:\n";
    print color('reset');

    my @maps = glob("$MAPS_DIR/*.rt");
    my $i = 1;

    foreach my $map (@maps)
    {
        printf "%2d) %s\n", $i++, basename($map);
    }

    print "\n";
    print color('bold cyan');
    print "Enter map number (1-$#maps) or 'all': ";
    print color('reset');

    my $input = <STDIN>;
    chomp $input;

    if (lc($input) eq 'all')
    {
        return @maps;
    }
    elsif ($input =~ /^\d+$/ && $input >= 1 && $input <= scalar @maps)
    {
        return $maps[$input - 1];
    }

    return "$MAPS_DIR/$DEFAULT_MAP";
}

# Main execution
print_header("MINIRT MEMORY TESTER");

# Validate executable
die color('bold red') . "Missing executable: $EXECUTABLE\n" . color('reset')
    unless -x $EXECUTABLE;

# Get map selection
my @selected_maps;
my $selection = select_map();

if (ref($selection) eq 'ARRAY')
{
    @selected_maps = @$selection;
}
else
{
    @selected_maps = ($selection);
}

# Process maps
foreach my $map (@selected_maps)
{
    next unless -e $map;

    my $log_file = run_valgrind($map);
    report_leaks($log_file);
}

print_header("TESTING COMPLETE");
