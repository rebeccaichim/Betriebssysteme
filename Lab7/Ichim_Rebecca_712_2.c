#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    char buffer[BUFFER_SIZE];
    pid_t pid;

    // Create the unnamed pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process (server)

        // Close the write end of the pipe
        close(pipefd[1]);

        // Read the directory name from the pipe
        read(pipefd[0], buffer, BUFFER_SIZE);

        // Close the read end of the pipe
        close(pipefd[0]);

        // Open the directory
        DIR *dir = opendir(buffer);
        if (dir == NULL) {
            fprintf(stderr, "Directory does not exist\n");
            return 1;
        }

        // Read the directory entries
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            // Filter text files
            if (strstr(entry->d_name, ".txt") != NULL) {
                printf("%s/%s\n", buffer, entry->d_name);
            }
        }

        // Close the directory
        closedir(dir);
    } else {
        // Parent process (client)

        // Close the read end of the pipe
        close(pipefd[0]);

        printf("Enter a directory name: ");
        fflush(stdout);

        // Read the directory name from the user
        fgets(buffer, BUFFER_SIZE, stdin);

        // Remove the newline character from the directory name
        buffer[strcspn(buffer, "\n")] = '\0';

        // Write the directory name to the pipe
        write(pipefd[1], buffer, strlen(buffer) + 1);

        // Close the write end of the pipe
        close(pipefd[1]);
    }

    return 0;
}
