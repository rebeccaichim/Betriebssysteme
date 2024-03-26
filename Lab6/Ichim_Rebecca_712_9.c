#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define NUM_PROCESSES 3

// Function to remove vowels from a portion of the string
void remove_vowels(char *str, int start, int end) {
    for (int i = start; i < end; i++) {
        if (isspace(str[i])) {
            continue;  // Skip spaces
        }

        if (strchr("aeiouAEIOU", str[i]) != NULL) {
            for (int j = i; j < end - 1; j++) {
                str[j] = str[j + 1];  // Shift characters to remove the vowel
            }
            str[end - 1] = '\0';  // Null-terminate the string
            end--;  // Decrease the range length
            i--;  // Decrement 'i' to recheck the current position
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("No string provided.\n");
        return 1;
    }

    char *str = argv[1];  // Get the string from command-line argument
    int str_length = strlen(str);
    int chunk_size = (str_length + NUM_PROCESSES - 1) / NUM_PROCESSES;

    int i;

    // Creating child processes
    for (i = 0; i < NUM_PROCESSES; i++) {
        if (fork() == 0) {
            // Child process
            int start = i * chunk_size;
            int end = start + chunk_size;
            if (end > str_length) {
                end = str_length;
            }
            remove_vowels(str, start, end);
            exit(0);
        }
    }

    // Waiting for child processes to complete
    for (i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    // Removing any remaining vowels from the entire string
    for (int i = 0; i < str_length; i++) {
        if (isspace(str[i])) {
            continue;  // Skip spaces
        }
        if (str[i] == '\0') {
            break;  // Stop processing at null terminator
        }
        if (strchr("aeiouAEIOU", str[i]) != NULL) {
            for (int j = i; j < str_length - 1; j++) {
                str[j] = str[j + 1];  // Shift characters to remove the vowel
            }
            str[str_length - 1] = '\0';  // Null-terminate the string
            i--;  // Decrement 'i' to recheck the current position
        }
    }

    // Printing the modified string
    printf("Modified string: %s\n", str);

    return 0;
}
