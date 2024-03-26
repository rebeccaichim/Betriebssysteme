#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

int main()
{
    int fd;
    char filename[100];
    int num_lines;

    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the FIFO pipe for writing
    fd = open(FIFO_NAME, O_WRONLY);

    // Send the filename to the server
    write(fd, filename, sizeof(filename));

    // Close the FIFO pipe
    close(fd);

    // Open the FIFO pipe for reading
    fd = open(FIFO_NAME, O_RDONLY);

    // Read the number of lines from the server
    read(fd, &num_lines, sizeof(int));

    printf("The number of lines in the file %s is: %d\n", filename, num_lines);

    // Close the FIFO pipe
    close(fd);

    return 0;
}
