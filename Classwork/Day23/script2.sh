#!/bin/bash
: 'script for accepting name and age as command line args and displays a personalized greeting and validate argument count.
 '

echo "welcome user:$1"
echo "your age:$2"

echo "args count:$#"