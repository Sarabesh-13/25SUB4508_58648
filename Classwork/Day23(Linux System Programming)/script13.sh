#!/bin/bash
: 'pass file name to function it should return the size and permission'

file_Details()
{
    local file="$1"
    echo "File name: $file"
    echo "File size and permission->$(ls -lhis $file)"
}


file_Details "$1"