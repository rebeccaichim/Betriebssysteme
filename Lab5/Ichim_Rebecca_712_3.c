#include <stdio.h>//input-output library
#include <stdlib.h>//memory allocation, string conversion
#include <ctype.h>//manipulating characters

int main(int argc, char *argv[]) {
    // Check if the program was called with two arguments (the project name and the file name).
    // If not, print an error message and exit with an error code of 1.
    if (argc != 2) {
        printf("Trebuie un nume de fișier ca argument în linia de comandă!\n");
        exit(1);
    }

    // Open the file specified by the command line argument for reading.
    // If the file cannot be opened, print an error message and exit with an error code of 1.
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Nu am putut deschide fișierul %s\n", argv[1]);
        exit(1);
    }

    // Initialize variables to keep track of the current word count and whether
    // the current character is part of a word or not.
    int wordCount = 0;
    int inWord = 0;
    int c;

    // Loop through each character in the file until the end of the file is reached.
    // If a space character is encountered, check if we were previously in a word.
    // If so, increment the word count and reset the inWord flag.
    // If a non-space character is encountered, set the inWord flag.
    // If a newline character is encountered, print the word count for that line,
    // reset the word count and inWord flag.
    while ((c = fgetc(fp)) != EOF) {
        if (isspace(c)) {
            if (inWord) {
                wordCount++;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
        if (c == '\n') {
            printf("%d \n", wordCount);
            wordCount = 0;
            inWord = 0;
        }
    }

    // If the file ends with a word, increment the word count and print it.
    if (inWord) {
        wordCount++;
    }
    if (wordCount > 0) {
        printf("%d \n", wordCount);
    }

    // Close the file 
    fclose(fp);
    return 0;
}

