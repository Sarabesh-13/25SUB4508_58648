#!/bin/bash
: ' write a script to accept a file and check it is readable writable and executable
   and display result correctly'

read -p "enter the filename:" file

if [ ! -e "$file" ]; then
   echo "file does'nt exist"
   exit 1
fi 

echo "File : $file"

[ -r "$file" ] && echo "Read allowed" || echo "Read not allowed"
[ -w "$file" ] && echo "Write allowed" || echo "Write not allowed"
[ -x "$file" ] && echo "Execute allowed" || echo "Execute not allowed"

echo

if [ -r "$file" ]; then
   echo "FIlE CONTENTS"
   cat "$file"
else
    echo "Can't Read Contents of the File"
fi 
