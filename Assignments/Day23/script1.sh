#!/bin/bash
: 'Task-3
   script to accept two variables of (string and int) and use if else to print the statment based on the input'

read -p "enter the number:" num

if ((num==0)); then
   str="Success"
   echo "$str"
else
   str="Failed"
   echo "$str"
fi