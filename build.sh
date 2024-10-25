#!/bin/sh

files=$(find . -type f -name "*.c")
flags="-Wall -Wextra -O2"
exe="ansh"

echo "Compiling:\n$files\nThis might take a while..."
gcc $flags -o $exe $files

