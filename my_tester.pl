#!/usr/bin/perl
use strict;
use warnings;
use File::Basename;
use Term::ANSIColor;
use IPC::Open3;
use Symbol 'gensym';

# Global hash to store test results: 1 for pass, 0 for fail.
my %test_results;

# Run a command with a timeout (in seconds) using IPC::Open3.
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
    return ($output, $timed_out);
}

# Print a formatted header for a map test.
sub print_header {
    my ($formatted_name) = @_;
    my $header_text = " TESTING MAP: '$formatted_name' ";
    my $line = "=" x (length($header_text) + 2);
    print colored("tester: $line\n", 'white');
    print colored("tester: |$header_text|\n", 'white');
    print colored("tester: $line\n", 'white');
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
    my ($output, $timed_out) = run_command("$miniRT $full_path", 1);
    
    (my $base_name = $map_file) =~ s/\.rt$//;
    (my $formatted_name = $base_name) =~ s/_/ /g;
    
    print "\n";
    print_header($formatted_name);
    
    if (exists $map_descriptions{$base_name}) {
        print colored(":>> $map_descriptions{$base_name}\n", 'yellow');
    }
    
    if ($timed_out) {
        print colored("❌ Timeout reached. ESC simulated.\n", 'red');
        $test_results{$base_name} = 0;
    } else {
        print colored("✅ Test passed.\n", 'green');
        $test_results{$base_name} = 1;
    }
    
    print colored("The Perl tester: ---------------------------------\n", 'white');
}

# Print per-map summary (sorted by numeric prefix).
print "\n", colored("Test Summary:\n", 'white');
foreach my $map (sort {
    my ($num_a) = $a =~ /^(\d+)_/;
    my ($num_b) = $b =~ /^(\d+)_/;
    ($num_a ? $num_a : 0) <=> ($num_b ? $num_b : 0)
} keys %test_results) {
    (my $pretty = $map) =~ s/_/ /g;
    my $status = $test_results{$map} ? colored("✅", 'green') : colored("❌", 'red');
    print colored("Map '$pretty': $status\n", 'white');
}

