#!/bin/bash

grep -l "$1" "${@:2}"  #this function uses grep to search the first argument $1 in the files given by the second argument. 
#-l is used to print the files that contain the first argument
