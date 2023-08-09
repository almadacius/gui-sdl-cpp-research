#!/usr/bin/env bash

function main () {
	local HERE=$(cd $(dirname $BASH_SOURCE) && pwd -P)
	local projRoot=$(cd "$HERE/../.." && pwd -P)

	local frameworkDir="$projRoot/c_modules/frameworks"
	local frameworkDir="$projRoot/c_modules/frameworks/SDL2_ttf.framework"
	local buildDir="$projRoot/build"

	# export DYLD_LIBRARY_PATH="$frameworkDir:$DYLD_LIBRARY_PATH"
	export DYLD_FALLBACK_LIBRARY_PATH="$frameworkDir:$DYLD_FALLBACK_LIBRARY_PATH"

	echo "aaa $DYLD_LIBRARY_PATH"

	cd "$buildDir"
	./app
}

( main $@ )
