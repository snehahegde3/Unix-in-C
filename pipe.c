/*
heres an example of a program that takes in a int value from the child process
and sends over to the parent that does the processing
using pipes
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // a pipe is a file that we can write and read from
    int fd[2];
    // the two ends of the pipe
    // fd[0] --> read end
    // fd[1] --> wtite end

    // takes an array of two integers -> file descriptors
    if (pipe(fd) == -1)
    {
        printf("Error occured while oepening the pipe\n ");
        return 1;
    }
    // when we fork, the fds get copied over
    // not only are they copied over, they get inherited
    // if closed in one end, remain open in another

    int id = fork();
    if (id == 0)
    {
        // no need to read anything hence close teh read end
        close(fd[0]);
        int x;
        printf("Enter the value: ");
        scanf("%d", &x);
        // writing to fd[1]
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            printf("Error while writing into pipe\n");
        }
        // close to mark the end of writing
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            printf("Error while reading from pipe\n");
        }
        close(fd[0]);
        printf("Sent from child process: %d\n", y);
    }
    return 0;
}
