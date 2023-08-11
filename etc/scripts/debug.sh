#!/usr/bin/env bash

function checkDebugSymbols () {
	lldb \
		-o "run" \
		-o "image list" \
		-o "quit" \
		./app
}

function main () {
	local HERE=$(cd $(dirname $BASH_SOURCE) && pwd -P)
	local projRoot=$(cd "$HERE/../.." && pwd -P)

	local buildDir="$projRoot/build"

	cd "$buildDir"

	# checkDebugSymbols
	lldb \
		-o "b test-sdl.cpp:8" \
		-o "run" \
		./app

	# set a breakpoint
	# - breakpoint set --file your_source_file.cpp --line 10
	# b file.c:13

	# run
	# - run
	# - image list - check if debug symbols are present

	# interact with breakpoints
	# - frame variable: Print local variables and their values.
	# - print variable_name: Print the value of a specific variable.
	# - step: Step into the next line of code.
	# - next: Step over to the next line of code.
	# - continue: Continue running until the next breakpoint.
	# - quit: Exit LLDB.

	# + during a breakpoint:
	# 	- expression @import @rpath
	# 	- image lookup @rpath
}

( main $@ )
