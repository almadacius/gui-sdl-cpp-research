#!/usr/bin/env bash

# a script to test a very basic compilation
# with sdl linked without the complexity of `@almadash/builder`

function main () {
  local HERE=$(dirname $BASH_SOURCE)
  local projRoot=$(cd "$HERE/../.." && pwd -P)

  cd "$projRoot/_tests-unit"

  local dist="$projRoot/build/app"

  g++ "test-sdl.cpp" \
    -o "$dist" \
    -std=c++11 \
    -I "/usr/local/include" \
    -L "/usr/local/lib" \
    -l SDL2
}

( main $@ )
