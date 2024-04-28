#!/usr/bin/perl

use strict;
use warnings;

system('valgrind --tool=memcheck \
	 --leak-check=full \
	 --show-leak-kinds=all \
	 --track-origins=yes \
	 --track-fds=yes \
	 --verbose  ./miniRT');



