#!/usr/bin/env bash

# a script to test a very basic compilation
# with sdl linked

function main () {
  local HERE=$(dirname $BASH_SOURCE)
  local projRoot=$(cd "$HERE/../.." && pwd -P)

  cd "$projRoot/src"

  local dist="$projRoot/build/app"

  g++ "main.cpp" \
    -o "$dist" \
    -std=c++11 \
    -I "/usr/local/include" \
    -L "/usr/local/lib" \
    -l SDL2
}

( main $@ )
