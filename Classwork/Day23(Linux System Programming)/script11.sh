#!/bin/bash
: 'print prime numbers from 1 and N'

echo "Enter the value of N:"
read N

echo "Prime numbers between 1 and $N are:"

for ((num=2; num<=N; num++))
do
    is_prime=1

    for ((i=2; i*i<=num; i++))
    do
        if (( num % i == 0 ))
        then
            is_prime=0
            break
        fi
    done

    if (( is_prime == 1 ))
    then
        echo -n "$num "
    fi
done

echo
