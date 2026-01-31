#!/bin/bash
: 'script for calculator using switch case'

echo "Calculator menu"
echo "1.Addition"
echo "2.Subtraction"
echo "3.Multiplication"
echo "4.Division"

read -p "enter your choice->" choice
read -p "enter the two numbers:" a b

case $choice in
    1)
     result=$((a+b))
     echo "Result: $result"
     ;;
    2)
      result=$((a-b))
      echo "Result: $result"
      ;;
    3)
      result=$((a*b))
      echo "Result $result"
      ;;
    4)
      if [ $b -eq 0 ];then
         echo "Division by zero"
      else
         result=$((a/b))
         echo "Result: $result"
      fi
      ;;
    *)
      echo "Invalid Choice"
      ;;
esac