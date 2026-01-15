#!/bin/bash
# Script to read a log file and display summary of INFO, WARNING and SUCCESS messages


if [ $# -ne 1 ]; then
    echo "Usage: $0 <log_file>"
    exit 1
fi

logfile="$1"   


if [ ! -f "$logfile" ]; then
    echo "Error: Log file does not exist"
    exit 2
fi


if [ ! -r "$logfile" ]; then
    echo "Error: No read permission for log file"
    exit 3
fi

info_count=$(grep -i "INFO" "$logfile" | wc -l)
warning_count=$(grep -i "WARNING" "$logfile" | wc -l)
success_count=$(grep -i "SUCCESS" "$logfile" | wc -l)


echo "INFO messages    : $info_count"
echo "WARNING messages : $warning_count"
echo "SUCCESS messages : $success_count"
