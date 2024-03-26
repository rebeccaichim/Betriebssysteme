#!/bin/bash

sed -E 's/[[:alnum:]]*[[:digit:]][[:alnum:]]*//g' file1.txt
#this function removes any string that contains at least one digit and may be proceded or followed by any other alphanumeric character in the file "file1.txt"
