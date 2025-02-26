#!/usr/bin/perl
use strict;
use warnings;
use Term::ANSIColor;
use IPC::Open3;
use Symbol 'gensym';

# Global variables
my %test_results;
my @map_files;
# Change based on local machine
my $wrong_dir = '/home/atucci/Desktop/miniRT/wrong_maps';
my $miniRT = './miniRT';

sub run_command {
    my ($cmd, $timeout) = @_;
    my $err = gensym;
    my $pid = open3(my $in, my $out, $err, $cmd);
    close $in;
    my $output = '';
    my $timed_out = 0;

    eval {
        local $SIG{ALRM} = sub {
            kill('SIGKILL', $pid);
            $timed_out = 1;
            die "timeout\n";
        };
        alarm($timeout);
        {
            local $/;
            $output .= defined $out ? <$out> : '';
            $output .= defined $err ? <$err> : '';
        }
        alarm(0);
    };
    if ($@ && $@ eq "timeout\n") {
        $output .= "TIMEOUT after ${timeout}s\n";
    }

    waitpid($pid, 0);
    return ($output, $timed_out, $? >> 8, $? & 127);
}

sub get_signal_name {
    my ($sig_num) = @_;
    return {
        1 => 'SIGHUP', 2 => 'SIGINT', 3 => 'SIGQUIT',
        4 => 'SIGILL', 6 => 'SIGABRT', 8 => 'SIGFPE',
        9 => 'SIGKILL', 11 => 'SIGSEGV', 13 => 'SIGPIPE',
        14 => 'SIGALRM', 15 => 'SIGTERM'
    }->{$sig_num} || "UNKNOWN";
}

sub format_test_result
{
    my ($passed) = @_;
    return $passed ? colored("PASS", 'green') : colored("FAIL", 'red');
}

sub print_summary_table {
    my @sorted_maps = sort {
        my ($num_a) = $a =~ /^(\d+)/;
        my ($num_b) = $b =~ /^(\d+)/;
        $num_a <=> $num_b
    } keys %test_results;

    # Header
    print colored("╔═════════════════════════════════════════════════════════╗\n", 'white');
    print colored("║ ", 'white') . colored(sprintf("%-20s", "MAP NAME"), 'white on_black')
          . colored("║ ", 'white') . colored(sprintf("%6s", "NORM"), 'white on_black')
          . colored("║ ", 'white') . colored(sprintf("%6s", "LEAKS"), 'white on_black')
          . colored("║ ", 'white') . colored(sprintf("%6s", "ERRORS"), 'white on_black')
          . colored("║\n", 'white');
    print colored("╠═════════════════════════════════════════════════════════╣\n", 'white');

    # Body
    for my $map (@sorted_maps) {
        my $res = $test_results{$map};
        printf colored("║ ", 'white')
              . colored(sprintf("%-28s", $map), 'white')
              . colored("║ ", 'white')
              . colored(sprintf("%6s", format_test_result($res->{normal})), 'white')
              . colored("║ ", 'white')
              . colored(sprintf("%6s", format_test_result($res->{leaks})), 'white')
              . colored("║ ", 'white')
              . colored(sprintf("%6s", format_test_result($res->{errors})), 'white')
              . colored("║\n", 'white');
    }

    # Footer
    print colored("╚═════════════════════════════════════════════════════════╝\n", 'white');
}

# Build executable if missing
if (!-e $miniRT && system('make') != 0)
{
    die colored("Failed to build miniRT\n", 'red');
}

# Get and sort test files numerically
opendir(my $dh, $wrong_dir) or die colored("Cannot open $wrong_dir: $!", 'red');
@map_files = map { "$wrong_dir/$_" } grep { /^\d+_.*\.rt$/ } readdir($dh);
closedir $dh;

@map_files = sort {
    my ($num_a) = $a =~ m{/(\d+)_};
    my ($num_b) = $b =~ m{/(\d+)_};
    $num_a <=> $num_b
} @map_files;

# Main testing logic
foreach my $map_file (@map_files) {
    my ($output, $timed_out, $exit_code, $signal) = run_command("$miniRT $map_file", 1);
	print("$miniRT $map_file\n");
    my $map_name = (split('/', $map_file))[-1];
    $map_name =~ s/\.rt$//;

    # Valgrind checks
    my ($vg_leaks, $vg_errors);
    my ($vg_out) = run_command("valgrind --leak-check=full $miniRT $map_file", 5);
    $vg_leaks = $vg_out =~ /no leaks are possible/ ? 1 : 0;

    ($vg_out) = run_command("valgrind --error-exitcode=42 $miniRT $map_file", 5);
    $vg_errors = ($vg_out =~ /ERROR SUMMARY: 0 errors/) ? 1 : 0;

    # Store results
    $test_results{$map_name} = {
        normal => !$signal && !$timed_out && $exit_code == 214,
        leaks => $vg_leaks,
        errors => $vg_errors
    };
}

# Display final results
print_summary_table();


