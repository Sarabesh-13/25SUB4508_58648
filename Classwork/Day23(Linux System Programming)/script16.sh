#!/bin/bash
# Script to copy a file from source to destination with error handling

if [ $# -ne 2 ]; then
    echo "Usage: $0 <source_file> <destination_path>"
    exit 1
fi

src="$1"        
dest="$2"       


if [ ! -e "$src" ]; then
    echo "Error: Source file does not exist"
    exit 2
fi

if [ ! -r "$src" ]; then
    echo "Error: No read permission on source file"
    exit 3
fi


if [ ! -d "$dest" ]; then
    echo "Error: Destination directory does not exist"
    exit 4
fi


if [ ! -w "$dest" ]; then
    echo "Error: No write permission on destination directory"
    exit 5
fi


cp "$src" "$dest"

# Check exit status of cp command
if [ $? -eq 0 ]; then
    echo "File copied successfully"
else
    echo "Error: File copy failed"
    exit 6
fi
