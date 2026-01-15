#1/bin/bash
: 'bash script for accepting marks as input and assign grades using if else statements'

read -p "enter your marks: " mark

echo -e "your mark:$mark"

if [ $mark -ge 90 ]; then
   echo "A+ Grade"
elif [ $mark -ge  80 ]; then
   echo "A Grade"
elif [ $mark -ge  70 ]; then
   echo "B Grade"
elif [ $mark -ge  60 ]; then
   echo "C Grade"
elif [ $mark -ge  50 ]; then
   echo "D Grade"
else
   echo "F Grade"
fi