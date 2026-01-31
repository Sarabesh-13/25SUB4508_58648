#!/bin/bash
: 'script to display top 5 most used command using sort and uniq'

echo "Top 5 most used commands:$(history | awk '{print $2}' | sort | uniq -c | sort -rn | head -n 5)"