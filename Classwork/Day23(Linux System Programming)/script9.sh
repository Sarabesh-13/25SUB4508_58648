#!/bin/bash
: 'script for looping through files in the directory and count the number of files by type extension'

read -p "enter the directory path to count file by extension types:" dir

dir=${dir%/} #removes slash here

if [ ! -d "$dir" ];then
   echo "directory does'nt exist"
   exit 1
fi

shopt -s nullglob #avoid *.ext files and nullglob avoid errors when no file matches

c_count=0
txt_count=0
cpp_count=0
sh_count=0
other_count=0

for file in "$dir"/*; do
    if [ -f "$file" ]; then
        case "$file" in
              *.c) ((c_count++)) ;;
              *.txt) ((txt_count++)) ;;
              *.cpp) ((cpp_count++)) ;;
              *.sh)  ((sh_count++)) ;;
              *)     ((other_count++)) ;;
        esac
    fi
done

#file count print extension
echo "C files: $c_count"
echo "txt files: $txt_count"
echo "cpp files: $cpp_count"
echo "bash script files: $sh_count"
echo "other files: $other_count" 