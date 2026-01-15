#!/bin/bash
# Task-4 script for looping through files in a directory and counting lines by extension


read -p "enter the directory path to count file by extension types:" dir

dir=${dir%/} #removes slash here

if [ ! -d "$dir" ];then
   echo "directory does'nt exist"
   exit 1
fi

shopt -s nullglob #avoid *.ext files and nullglob avoid errors when no file matches



count()
{
    local file="$1"
    echo "File name:$file"
    echo "Number of lines in file $(wc -l < "$file")"
}


for file in "$dir"/*; do
    [ -f "$file" ] || continue
    case "$file" in
        *.c|*.txt|*.cpp|*.sh) 
                count "$file" 
                ;;
    esac
done
