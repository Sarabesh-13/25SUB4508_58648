#!/bin/bash
: 'Task-5
   script to use grep command to find list of all occurence of specific word in a given file and pipe output to sort alphabetically'

if [[ $# -eq 0 ]]; then
   echo "Usage: $0 <WORD_TO_SEARCH> <FILE_PATH>"
   exit 1

echo "List of occurence of word in a file $(grep "$1" "$2" | sort)"