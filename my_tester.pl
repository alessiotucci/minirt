#!/usr/bin/perl
use strict;
use warnings;
use Term::ANSIColor;
use IPC::Open3;
use Symbol 'gensym';

# Global variables
my %test_results;
my @map_files;
# Change these paths as needed
my $wrong_dir = '/nfs/homes/atucci/Desktop/mioGithubMiniRT/wrong_maps';
my $miniRT    = './miniRT';

# Run a command with a timeout and return (output, timed_out, exit_code, signal)
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

# Convert a signal number to its name
sub get_signal_name {
    my ($sig_num) = @_;
    return {
        1  => 'SIGHUP', 2  => 'SIGINT', 3  => 'SIGQUIT',
        4  => 'SIGILL', 6  => 'SIGABRT', 8  => 'SIGFPE',
        9  => 'SIGKILL', 11 => 'SIGSEGV', 13 => 'SIGPIPE',
        14 => 'SIGALRM', 15 => 'SIGTERM'
    }->{$sig_num} || "UNKNOWN";
}

# Determine emoji for the normal test.
# Expected: exit code 214 → PASS (✅)
# If a segfault occurs (signal==11 or exit code 139) → skull (💀)
# Otherwise → red cross (❌)
sub normal_emoji {
    my ($timed_out, $exit_code, $signal) = @_;
    if ($timed_out) {
        return "❌";
    } elsif ($signal) {
        return ($signal == 11) ? "💀" : "❌";
    } elsif ($exit_code == 214) {
        return "✅";
    } elsif ($exit_code == 139) {
        return "💀";
    } else {
        return "❌";
    }
}

# For leak and error checks: if the regex matches, return green check, else red cross.
sub simple_emoji {
    my ($passed) = @_;
    return $passed ? "✅" : "❌";
}

# Print final summary table with adjusted column widths.
sub print_summary_table {
    my $map_col_width  =  thirty();  # We'll set a width of 30 characters.
    my $test_col_width = 8;
    my @sorted_maps = sort {
        my ($num_a) = $a =~ /^(\d+)/;
        my ($num_b) = $b =~ /^(\d+)/;
        $num_a <=> $num_b
    } keys %test_results;

    # Header
    print colored("╔" . "═" x ( $map_col_width + 3 + 3*$test_col_width + 4 ) . "╗\n", 'white');
    printf colored("║ %-*s║ %*s║ %*s║ %*s║\n", 'white'),
        $map_col_width, "MAP NAME",
        $test_col_width, "NORM",
        $test_col_width, "LEAKS",
        $test_col_width, "ERRORS";
    print colored("╠" . "═" x ( $map_col_width + 3 + 3*$test_col_width + 4 ) . "╣\n", 'white');

    # Body
    foreach my $map (@sorted_maps) {
        my $res = $test_results{$map};
        my $norm_icon = normal_emoji($res->{normal}{timed_out}, $res->{normal}{exit_code}, $res->{normal}{signal});
        my $leak_icon  = simple_emoji($res->{leaks});
        my $error_icon = simple_emoji($res->{errors});
        printf colored("║ %-*s  %*s  %*s  %*s \n", 'white'),
            $map_col_width, $map,
            $test_col_width, $norm_icon, #update here
            $test_col_width, $leak_icon,
            $test_col_width, $error_icon;
    }

    # Footer
    print colored("╚" . "═" x ( $map_col_width + 3 + 3*$test_col_width + 4 ) . "╝\n", 'white');
}

# Helper: return fixed column width for map names
sub thirty { return 30; }

# Build executable if missing
if (!-e $miniRT && system('make') != 0) {
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
    # Get only the basename (e.g. 4_empty_map.rt)
    my $map_name_full = (split('/', $map_file))[-1];
    (my $map_name = $map_name_full) =~ s/\.rt$//;

    # Run normal test (suppress miniRT's output)
    my ($output, $timed_out, $exit_code, $signal) =
         run_command("$miniRT $map_file > /dev/null 2>&1", 1);
    my $norm_icon = normal_emoji($timed_out, $exit_code, $signal);
    
    # Run Valgrind Leak Check (capture output for shallow test)
    my ($vg_out, $vg_timed_out, $vg_exit_code, $vg_signal) =
         run_command("valgrind --leak-check=full $miniRT $map_file", 5);
    my $leak_pass = ($vg_out =~ /no leaks are possible/) ? 1 : 0;
    my $leak_icon = simple_emoji($leak_pass);
    
    # Run Valgrind Error Check
    ($vg_out, $vg_timed_out, $vg_exit_code, $vg_signal) =
         run_command("valgrind --error-exitcode=42 $miniRT $map_file", 5);
    my $error_pass = ($vg_out =~ /ERROR SUMMARY: 0 errors/) ? 1 : 0;
    my $error_icon = simple_emoji($error_pass);

    # Print one-line feedback (only map basename and three icons)
    print "Executing: $miniRT $map_name_full  $norm_icon $leak_icon $error_icon\n";

    # Store results for summary table (using the short map name)
    $test_results{$map_name} = {
        normal => {
            exit_code => $exit_code,
            timed_out => $timed_out,
            signal    => $signal,
        },
        leaks  => $leak_pass,
        errors => $error_pass,
    };
}

# Display final summary table
print "\nFinal Summary:\n";
print_summary_table();

