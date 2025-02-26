#!/usr/bin/perl
use strict;
use warnings;
use File::Basename;
use Term::ANSIColor;
use IPC::Open3;
use Symbol 'gensym';

# Global variables
my %test_results;
my @map_files;
my $wrong_dir = '/nfs/homes/atucci/Desktop/mioGithubMiniRT/wrong_maps';
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
            $output .= <$out> if $out;
            $output .= <$err> if $err;
        }
        alarm(0);
    };
    if ($@ && $@ eq "timeout\n") {
        $output .= "TIMEOUT after ${timeout}s\n";
    }
    
    waitpid($pid, 0);
    my $exit_code = $? >> 8;
    my $signal = $? & 127;
    
    return ($output, $timed_out, $exit_code, $signal);
}

sub get_signal_name {
    my ($sig_num) = @_;
    return {
        1 => 'SIGHUP', 2 => 'SIGINT', 3 => 'SIGQUIT',
        4 => 'SIGILL', 6 => 'SIGABRT', 8 => 'SIGFPE',
        9 => 'SIGKILL', 11 => 'SIGSEGV', 13 => 'SIGPIPE',
        14 => 'SIGALRM', 15 => 'SIGTERM'
    }->{$sig_num} || "UNKNOWN_SIGNAL";
}

sub prompt_user
{
    print colored("Press ENTER to continue...", 'yellow');
    <STDIN>;
}

sub print_test_result
{
    my ($label, $passed, $message) = @_;
    my $color = $passed ? 'green' : 'red';
    my $icon = $passed ? '✅' : '💀';
    print colored(sprintf("tester: %-12s %s %s\n", $label, $icon, $message), $color);
}

sub print_header
{
    my ($formatted_name) = @_;
    my $header_text = " TESTING MAP: '$formatted_name' ";
    my $line = "=" x (length($header_text) + 2);
    print colored("tester: $line\n", 'white');
    print colored("tester: |$header_text|\n", 'white');
    print colored("tester: $line\n", 'white');
}

sub print_ascii_box {
    my ($title, $content) = @_;
    my @lines = split /\n/, $content;
    my $max_length = length($title);
    for my $line (@lines) {
        $max_length = length($line) if length($line) > $max_length;
    }
    my $border = "|" . ("+" x ($max_length + 2)) . "|\n";
    print colored($border, 'white');
    printf colored("| %-" . $max_length . "s |\n", 'white'), $title;
    print colored($border, 'white');
    for my $line (@lines) {
        printf colored("| %-" . $max_length . "s |\n", 'white'), $line;
    }
    print colored($border, 'white');
}

# Initialize miniRT executable
if (!-e $miniRT) {
    system('make') == 0 or die colored("Failed to build miniRT\n", 'red');
}

# Collect and sort map files
opendir my $dh, $wrong_dir or die colored("tester: Could not open '$wrong_dir': $!\n", 'red');
@map_files = grep { -f "$wrong_dir/$_" && /\.rt$/ } readdir($dh);
closedir $dh;

@map_files = sort {
    my ($num_a) = $a =~ /^(\d+)/;
    my ($num_b) = $b =~ /^(\d+)/;
    $num_a //= 9999;  # Se non c'è numero, mettilo in fondo alla lista
    $num_b //= 9999;
    $num_a <=> $num_b || $a cmp $b;
} @map_files;

# Main test loop
foreach my $map_file (@map_files) {
    my $full_path = "$wrong_dir/$map_file";
    
    # Normal run with 2-second timeout
    my ($output, $timed_out, $exit_code, $signal) = run_command("$miniRT $full_path", 2);
    my $crashed = $signal ? 1 : 0;
    my $map_base = $map_file;
    $map_base =~ s/\.rt$//;
    
    print_header($map_base);
    print_ascii_box("NORMAL RUN OUTPUT", $output);
    
    if ($crashed) {
        my $sig_name = get_signal_name($signal);
        print_test_result('CRASH', 0, "Crashed with $sig_name ($signal)");
    }
    elsif ($timed_out) {
        print_test_result('TIMEOUT', 0, "Exceeded 2s timeout");
    }
    else {
        print_test_result('EXIT CODE', $exit_code == 0, "Exit code: $exit_code");
    }
    
    # Valgrind leak check
    prompt_user();
    my ($vg_out, $vg_to, $vg_ec, $vg_sig) = run_command(
        "valgrind --leak-check=full $miniRT $full_path", 2
    );
    my $vg_leaks = $vg_out =~ /no leaks are possible/ ? 1 : 0;
    print_ascii_box("VALGRIND LEAK CHECK", $vg_out);
    print_test_result('LEAK CHECK', $vg_leaks, $vg_leaks ? "Clean" : "Memory leaks detected");
    
    # Valgrind error check
    prompt_user();
    ($vg_out, $vg_to, $vg_ec, $vg_sig) = run_command(
        "valgrind --error-exitcode=42 $miniRT $full_path", 2
    );
    my $vg_errors = ($vg_ec == 42 || $vg_sig) ? 0 : 1;
    print_ascii_box("VALGRIND ERROR CHECK", $vg_out);
    print_test_result('ERROR CHECK', $vg_errors, $vg_errors ? "Clean" : "Valgrind errors found");
    
    # Store results
    $test_results{$map_base} = {
        normal => !$crashed && !$timed_out && ($exit_code == 0),
        leaks => $vg_leaks,
        errors => $vg_errors
    };
    
    print colored("\ntester: " . ("-"x50) . "\n", 'white');
}

# Print final summary
print "\n" . colored("tester: FINAL SUMMARY RESULTS\n", 'bold white');
print colored("tester: " . ("="x50) . "\n", 'white');

foreach my $map (sort keys %test_results) {
    my $res = $test_results{$map};
    printf colored("%-25s", 'white'), $map;
    print colored("NORMAL: ", 'white');
    print $res->{normal} ? colored("PASS", 'green') : colored("FAIL", 'red');
    print colored("  LEAKS: ", 'white');
    print $res->{leaks} ? colored("PASS", 'green') : colored("FAIL", 'red');
    print colored("  ERRORS: ", 'white');
    print $res->{errors} ? colored("PASS", 'green') : colored("FAIL", 'red');
    print "\n";
}
