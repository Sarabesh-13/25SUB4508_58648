#!/bin/bash
: 'script for number guessing game'

number=$((RANDOM%50+1))

while :; do
    echo $number
    read -p "enter the number you have guessed:" guess
    if [ $number -eq $guess ]; then
       echo "you have correctly guessed the number"
       break
    elif [ $guess -gt $number ]; then
        echo "too high"
    else
        echo "too low"
    fi
done