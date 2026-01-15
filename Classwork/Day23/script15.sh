#!/bin/bash
: 'script to run properly and enable debug mode if flag -d passed'

if [ "$1" = "-d" ]; then
    # Enable debug mode
    set -x
    echo "Debug mode enabled"
fi

a=10
b=20
sum=$((a + b))

echo "Value of a: $a"
echo "Value of b: $b"
echo "Sum: $sum"

echo "Script finished"