#!/usr/bin/perl
use strict;
use warnings;
use File::Basename;
use Term::ANSIColor;
use IPC::Open3;
use Symbol 'gensym';

# Global hash to store test results for each map.
# Each entry is a hashref: { normal => 1|0, valgrind => 1|0 }
my %test_results;

sub run_command {
    my ($cmd, $timeout) = @_;
    my $err = gensym;
    my $pid = open3(my $in, my $out, $err, $cmd);
    close $in;  # No input.
    my $output = '';
    my $timed_out = 0;

    eval {
        local $SIG{ALRM} = sub {
            kill('SIGINT', $pid);
            $timed_out = 1;
            die "timeout\n"
        };
        alarm($timeout);
        {
            local $/;
            $output .= <$out> if $out;
            $output .= <$err> if $err;
        }
        alarm(0);
    };
    if ($@) {
        if ($@ eq "timeout\n") {
            $output .= "Timeout reached after $timeout second(s), process killed. Simulated ESC key press.\n";
        } else {
            $output .= "Error: $@";
        }
    }
    waitpid($pid, 0);
    my $exit_code = $? >> 8;

    # Check for segmentation fault or bus error
    if ($output =~ /Segmentation fault|Bus error/) {
        print colored("tester: 💀 Fatal error detected! (Segfault or Bus error)\n", 'red');
    }

    return ($output, $timed_out, $exit_code);
}

# Run a command with a timeout (in seconds) using IPC::Open3.
# Returns: (output, timed_out flag, exit_code)
# sub run_command {
#     my ($cmd, $timeout) = @_;
#     my $err = gensym;
#     my $pid = open3(my $in, my $out, $err, $cmd);
#     close $in;  # No input.
#     my $output = '';
#     my $timed_out = 0;
# 
#     eval {
#         local $SIG{ALRM} = sub {
#             kill('SIGINT', $pid);
#             $timed_out = 1;
#             die "timeout\n"
#         };
#         alarm($timeout);
#         {
#             local $/;
#             $output .= <$out> if $out;
#             $output .= <$err> if $err;
#         }
#         alarm(0);
#     };
#     if ($@) {
#         if ($@ eq "timeout\n") {
#             $output .= "Timeout reached after $timeout second(s), process killed. Simulated ESC key press.\n";
#         } else {
#             $output .= "Error: $@";
#         }
#     }
#     waitpid($pid, 0);
#     my $exit_code = $? >> 8;
#     return ($output, $timed_out, $exit_code);
# }

# Print a formatted header for a map test.
sub print_header {
    my ($formatted_name) = @_;
    my $header_text = " TESTING MAP: '$formatted_name' ";
    my $line = "=" x (length($header_text) + 2);
    print colored("tester: $line\n", 'white');
    print colored("tester: |$header_text|\n", 'white');
    print colored("tester: $line\n", 'white');
}

# Print a string inside an ASCII art box with a given title.
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

# Path to the miniRT executable.
my $miniRT = './miniRT';
if ( ! -e $miniRT ) {
    system('make');
}

# Hash of map base names (snake_case) and their descriptions.
my %map_descriptions = (
    "1_map_without_extension"         => "File name does not have the .rt extension.",
    "3_map_cannot_open"                => "Map file cannot be opened due to permissions.",
    "4_empty_map"                      => "Map file is empty.",
    "5_invalid_identifier_map"         => "Contains an unknown identifier.",
    "6_invalid_ratio_map"              => "Ambient lighting ratio is out of allowed range [0.0,1.0].",
    "7_missing_color_sphere"           => "Sphere entry is missing the color field.",
    "8_invalid_xyz_sphere_map"         => "Coordinates for the sphere center are non-numeric.",
    "9_invalid_vector_cam"             => "Camera orientation vector is invalid.",
    "10_invalid_fov_map"               => "Camera FOV is out of allowed range [0,180].",
    "11_invalid_light_ratio_map"       => "Light brightness ratio is above 1.0.",
    "12_invalid_cylinder_missing_size" => "Cylinder entry is missing a required parameter (e.g., height).",
    "13_invalid_color_map"             => "Sphere’s color field contains an invalid format (e.g. '255%' instead of '255')."
);

# Folder containing the wrong maps.
my $wrong_dir = '/nfs/homes/atucci/Desktop/mioGithubMiniRT/wrong_maps';
opendir my $dh, $wrong_dir or die colored("tester: Could not open '$wrong_dir': $!\n", 'red');

# Collect and sort the map files by their numeric prefix.
my @map_files = grep { -f "$wrong_dir/$_" and !/^\.\.?$/ } readdir($dh);
closedir $dh;
@map_files = sort {
    my ($num_a) = $a =~ /^(\d+)_/;
    my ($num_b) = $b =~ /^(\d+)_/;
    ($num_a ? $num_a : 0) <=> ($num_b ? $num_b : 0)
} @map_files;

foreach my $map_file (@map_files) {
    my $full_path = "$wrong_dir/$map_file";

    # --- Normal run ---
    my ($output_normal, $timed_out_normal, $exit_code_normal) = run_command("$miniRT $full_path", 1);

    # --- Valgrind run ---
    my $valgrind_cmd = "valgrind --leak-check=full --error-exitcode=42 $miniRT $full_path";
    my ($vg_output, $vg_timed_out, $vg_exit_code) = run_command($valgrind_cmd, 5);

    # Check Valgrind output for the leak-free message.
    my $vg_passed = ($vg_output =~ /All heap blocks were freed -- no leaks are possible/) ? 1 : 0;

    (my $base_name = $map_file) =~ s/\.rt$//;
    (my $formatted_name = $base_name) =~ s/_/ /g;

    print "\n";
    print_header($formatted_name);

    if (exists $map_descriptions{$base_name}) {
        print colored("tester: >> $map_descriptions{$base_name}\n", 'yellow');
    }

    # Print miniRT normal run output.
    print_ascii_box("Output", $output_normal);

    # Print Valgrind output.
    print_ascii_box("Valgrind", $vg_output);

    # Determine test status for each run.
    my $normal_passed = (!$timed_out_normal && $exit_code_normal == 0) ? 1 : 0;

    my $overall = ($normal_passed && $vg_passed) ? 1 : 0;
    if (!$overall) {
        print colored("tester: ❌ Test failed (see above output).\n", 'red');
    } else {
        print colored("tester: ✅ Test passed.\n", 'green');
    }

    # Store both results in the hash.
    $test_results{$base_name} = { normal => $normal_passed, valgrind => $vg_passed };

    print colored("tester: ---------------------------------\n", 'white');
}

# Print per-map summary (sorted by numeric prefix).
print "\n", colored("tester: Test Summary:\n", 'white');
foreach my $map (sort {
    my ($num_a) = $a =~ /^(\d+)_/;
    my ($num_b) = $b =~ /^(\d+)_/;
    ($num_a ? $num_a : 0) <=> ($num_b ? $num_b : 0)
} keys %test_results) {
    (my $pretty = $map) =~ s/_/ /g;
    my $normal_status = $test_results{$map}->{normal} ? colored("✅", 'green') : colored("❌", 'red');
    my $vg_status = $test_results{$map}->{valgrind} ? colored("✅", 'green') : colored("❌", 'red');
    print colored("tester: Map '$pretty': Normal: $normal_status | Valgrind: $vg_status\n", 'white');
}
