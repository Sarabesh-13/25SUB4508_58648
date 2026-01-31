#!/bin/bash
: 'bash script for calculator based on user choice'

add() {
    echo "Result: $((a + b))"
}

sub() {
    echo "Result: $((a - b))"
}

mul() {
    echo "Result: $((a * b))"
}

div() {
    if [ "$b" -eq 0 ]; then
        echo "Error: Division by zero is not allowed"
    else
        echo "Result: $((a / b))"
    fi
}

echo "Enter first number:"
read a

echo "Enter second number:"
read b

echo "Choose operation:"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"

read choice

case $choice in
    1) add ;;
    2) sub ;;
    3) mul ;;
    4) div ;;
    *) echo "Invalid choice" ;;
esac
