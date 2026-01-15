#!/bin/bash
: 'script to accept process name and display pid and owner'

[ $# -ne 1 ] && { echo "Usage: $0 <process_name>"; exit 1; }

ps -C "$1" -o pid=,user= || echo "Process not found"
