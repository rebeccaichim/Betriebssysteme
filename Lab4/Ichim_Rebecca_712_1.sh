#!/bin/bash

# Checks if a file was given
if [ $# -eq 0 ]; then
echo "Usage: $0 <filename.c>"
exit 1
fi

# The file name is given in the first command line
filename="$1"

# Checks if the file exists
if [ ! -f "$filename" ]; then 
echo "$filename not found"
exit 1
fi

# Extract all function names from the .c file
# Searches for lines that begin with int and end with an opening paranthesis
# Extract the function name
functions=$(grep -E "^[[:blank:]]*int[[:blank:]]+\w+\(" "$filename" | sed -E 's/^[[:blank:]]*int[[:blank:]]+(\w+)\(.*/\1/')

# Iterates over the list of function names extracted and counts the number of times each function is called
for func in $functions; do
count=$(grep -o "\b$func\b" "$filename" | wc -l)
echo "$func $count"
done
