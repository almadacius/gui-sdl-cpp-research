#!/usr/bin/env bash

function main () {
	local HERE=$(cd $(dirname $BASH_SOURCE) && pwd -P)
	local projRoot=$(cd "$HERE/../.." && pwd -P)

	local frameworkDir="$projRoot/c_modules/frameworks"
	# local frameworkDir="@executable_path/../c_modules/frameworks"
	# local frameworkDir="$projRoot/c_modules/frameworks/SDL2_ttf.framework"
	local buildDir="$projRoot/build"

	# export DYLD_LIBRARY_PATH="$frameworkDir:$DYLD_LIBRARY_PATH"
	# export DYLD_LIBRARY_PATH="$frameworkDir"
	# export DYLD_FALLBACK_LIBRARY_PATH="$frameworkDir:$DYLD_FALLBACK_LIBRARY_PATH"
	# export LD_LIBRARY_PATH="$frameworkDir"
	# export LIBRARY_PATH="$frameworkDir"

	# this will print value of @rpath
	# does NOT seem to work when the binary fails to init
	# export DYLD_PRINT_RPATHS=1

	echo "DYLD_LIBRARY_PATH: $DYLD_LIBRARY_PATH"

	cd "$buildDir"
	./app
}

( main $@ )
