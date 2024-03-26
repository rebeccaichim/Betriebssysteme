#!/bin/bash

read -p "Enter a number: " num

#check if the number is less than or equal to 1
if [ $num -le 1 ]; then
echo "not prime"
exit 0
fi

#loop through all possible factors of the number
for (( i=2; i<$num; i++ )); do
#check if i is a factor of the number
if [ $((num%i)) -eq 0 ]; then
echo "not prime"
exit 0
fi
done

#if no factors were found, the number is prime
echo "prime"
