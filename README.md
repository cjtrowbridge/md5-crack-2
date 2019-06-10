# Sierra College: CSCI-0046
This is a C program which cracks md5 passwords from a dictionary.

## Lab 9: Cracking Passwords


In this assignment you will try your hand at cracking passwords. You will be able to generate a file containing cryptographic MD5 hashes, just the way they are stored in a typical password database. Your task is to write a program to crack the passwords by trying each of them against a dictionary of plaintext passwords.

https://www.youtube.com/watch?v=9qmfVWftR1s

### Working With Files
https://www.youtube.com/watch?v=G0edmzyLW-U

## Obtain the starter files
Fork and clone my BitBucket repository.

1. Open a web browser and go to https://bitbucket.org/profbbrown/crack2 (Links to an external site.)Links to an external site.
1. Fork the repository on BitBucket.
1. Clone the repository into your Cloud9 account.

## Create the hash file
Run this command: make hashes

This will create two files: hashes.txt and passwords.txt. The former contains the MD5 hashes; the latter contains their plaintext equivalents. The plaintext passwords are selected randomly from the rockyou100.txt file.

If you wish, you can change the number of hashes generated and the source file at the top of the Makefile. For example, change NUM_HASHES to 50 and ROCKYOU to rockyou2000.txt. Then run make hashes again.

## Modify the Makefile
The Makefile provided is mostly complete. You need to insert the recipes to build the crack.o and crack programs.

## Build the template programs
Run this command: make

This will compile the crack.c and md5.c files together and make a program called crack.

Run make test to run the crack program against the hashes.txt and rockyou100.txt files.

## Edit the C files
All the work you need to do is in the crack.c file. You do not need to modify md5.c.

The code in generously commented with descriptions of what needs to be done to make a single-threaded password cracker. Essentially, they are:

* Write the readfile function that reads in a file (one word per line) and returns a pointer to the array of strings.
* Modify tryguess() to hash a plaintext guess and compare it to another hash. Return 0 if they don't match; 1 if they do match.
* Modify main() to try each of the hashes against the dictionary of plaintext guesses. You will need two nested loops: one for the array of hashes, the other for the array of dictionary words. Within the loops, call tryguess to see if the hash matches the dictionary word. 

## What to Turn In
Push your version of the crack program to BitBucket.

Scoring is as follows:

9 points: Got the program working as described

1 point: Made some optimization changes that allows the crack program to work even faster. We talked in class about ideas for making the program "do less work per iteration."

## readfile function
(see screenshot files in repository)
