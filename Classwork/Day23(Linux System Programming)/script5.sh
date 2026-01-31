#!/bin/bash
: 'script for showing usage of readonly variable'

read -p "enter a value to make it readonly:" value
readonly value

echo "readonly value=$value"
value=50