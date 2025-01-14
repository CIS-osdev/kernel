#!/bin/bash

pwd=$(pwd)
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR/..

clang-format --style=file --dump-config
find ./ -iname '*.h' -o -iname '*.c' | xargs clang-format -i --style=file --verbose

cd $pwd
