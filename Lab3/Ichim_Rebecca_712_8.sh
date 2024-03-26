#!/bin/bash

awk '

BEGIN {

# Set the field separator to whitespace or comma
FS = "[[:space:],]+" 
sum=0
# Initialize the variable that counts fields containing numbers to 0
contains_number = 0 
# Initialize the variable that counts fields not containing numbers to 0
contains_no_number = 0 
}

{
valid = 0
# Iterate over all fields in the current line
for (i = 1; i <= NF; i++) { 
# Check if the current field contains a valid number
if ($i ~ /^[0-9]+(\.[0-9]+)?$/) {
sum += $i
# Set the valid variable to 1 to indicate that a valid number was found
valid = 1 
}
}

# If a valid number was found in the line
if (valid) { 
# Increment the variable that counts fields containing numbers
contains_number++ 
} else {
# Otherwise increment the variable that counts fields not containing numbers
contains_no_number++
}
}
END { 

# Calculate the ratio of fields containing numbers to fields ot containing numbers
ratio = contains_number == 0 ? contains_number ":0" :  contains_number ":" contains_no_number
print "Sum=" sum
print " Ratio contains_number/contains_no_number= " ratio
}' input_file.txt
