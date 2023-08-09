#!/usr/bin/env bash

function main () {
	local HERE=$(cd $(dirname $BASH_SOURCE) && pwd -P)
	local projRoot=$(cd "$HERE/../.." && pwd -P)

	local buildDir="$projRoot/build"

	cd "$buildDir"
	# summary deps
	otool -L ./app

	otool -l ./app
}

( main $@ )
