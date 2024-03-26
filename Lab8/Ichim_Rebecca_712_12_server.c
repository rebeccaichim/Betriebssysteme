#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

int count_lines(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
            count++;
    }

    fclose(file);
    return count;
}

int main()
{
    int fd;
    char filename[100];
    int num_lines;

    // Create the FIFO pipe (if it doesn't exist already)
    mkfifo(FIFO_NAME, 0666);

    // Open the FIFO pipe for reading
    fd = open(FIFO_NAME, O_RDONLY);

    // Read the filename from the client
    read(fd, filename, sizeof(filename));

    // Calculate the number of lines in the file
    num_lines = count_lines(filename);
 // Close the FIFO pipe
    close(fd);

    // Print the number of lines in the file
    printf("The number of lines in the file %s is: %d\n", filename, num_lines);

    // Remove the FIFO file
    unlink(FIFO_NAME);

    return 0;
}
