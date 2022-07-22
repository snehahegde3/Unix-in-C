
/*
three processes
process 1 creates a x, sends to the next which adds 5
sends to the next which adds 5 again
sends it back to original
                          ________________
                         |               |
                         |       x       |
                         |_______________|
                         |               |
                         |               |
                  _______|_______  ______|________
                 |              | |              |
                 |     x+5      | |      x+5     |
                 |______________| |______________|
so we need three pipes, 6 file descriptors in the main process
these are inherited by the child processes
so 6*3 = 18 file descriptors
fd[3][2]
                            fd[0][1]
                          ________________  fd[2][0]
                         |               |
                         |       x       |
                         |_______________|
                         |               |
             fd[0][0]    |               |  fd[2][1]
                  _______|_______  ______|________
                 |              | |              |
                 |     x+5      | |      x+5     |
                 |______________|_|______________|
                     fd[1][1]         fd[1][0]
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd[3][2];
    int i;
    for (i = 0; i < 3; i++)
    {
        if (pipe(fd[i]) < 0)
        {
            printf("failed to create pipe\n");
            return 1;
        }
    }

    int x;
    printf("Input number: ");
    scanf("%d", &x);
    if (write(fd[0][1], &x, sizeof(int)) < 0)
    {
        printf("write failed\n");
        return 8;
    }

    int pid1 = fork();
    if (pid1 < 0)
    {
        printf("failed to fork\n");
        return 2;
    }
    if (pid1 == 0)
    {
        // child process 1
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        int x;
        if (read(fd[0][0], &x, sizeof(int)) < 0)
        {
            printf("read failed\n");
            return 3;
        }
        // printf("%d\n", x);
        x += 5;
        // printf("%d\n", x);
        if (write(fd[1][1], &x, sizeof(int)) < 0)
        {
            printf("write failed\n");
            return 4;
        }
        close(fd[0][0]);
        close(fd[1][1]);
        return 0;
    }

    int pid2 = fork();
    if (pid2 < 0)
    {
        printf("failed to fork\n");
        return 5;
    }
    if (pid2 == 0)
    {
        // child process 2
        close(fd[0][1]);
        close(fd[2][0]);
        close(fd[0][0]);
        close(fd[1][1]);
        int x;
        if (read(fd[1][0], &x, sizeof(int)) < 0)
        {
            printf("read failed\n");
            return 6;
        }
        // printf("%d\n", x);
        x += 5;
        // printf("%d\n", x);
        if (write(fd[2][1], &x, sizeof(int)) < 0)
        {
            printf("write failed\n");
            return 7;
        }
        close(fd[1][0]);
        close(fd[2][1]);
        return 0;
    }

    // parent process

    if (read(fd[2][0], &x, sizeof(int)) < 0)
    {
        printf("read failed\n");
        return 9;
    }
    close(fd[0][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    close(fd[1][0]);
    close(fd[0][1]);
    close(fd[2][0]);

    printf("Result is %d\n", x);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}