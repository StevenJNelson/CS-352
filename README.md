# CS 352 - Lab 1

## by David Edwardson & Steven Nelson

## Computer Architecture - Fall 2018

###To compile/run:
1. make run

###To clean-up: 
1. make clean

## README
This is our implementation of a checksum.

Our program prompts for input and takes in the name of a file.
The file is then passed to a function that generates a 
code (in hex) using ones compliment arithmetic. That code
is passed to a function that compares the first code
with the code of another file and reports if they are the 
same file or not. This also works on large files as we have tested.

## Issues encountered

Our biggest issue was figuring out how to properly break the file
into 32 bit chunks.




