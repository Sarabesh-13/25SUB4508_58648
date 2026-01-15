#!/bin/bash
: 'script to extract usernames and shells from /etc/passwd and display users only with /bin/bash using pipe and filter'

echo -e "Users from /bin/bash:\n $(cut -d: -f1,7 /etc/passwd | grep "/bin/bash")"