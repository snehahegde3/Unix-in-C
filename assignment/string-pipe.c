#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("Failure while creating pipe\n");
        return 1;
    }
    int pid = fork();
    if (pid == -1)
    {
        printf("Failure while fork()\n");
        return 2;
    }
    if (pid == 0)
    {
        close(fd[0]);
        char str[200];
        int n;
        printf("Input string : ");
        fgets(str, 200, stdin);

        // set last char
        str[strlen(str) - 1] = '\0';
        n = strlen(str) + 1;

        // send the length of string
        if (write(fd[1], &n, sizeof(int)) == -1)
        {
            printf("Failed to write\n");
            return 3;
        }
        //  write into write end
        if (write(fd[1], str, strlen(str) + 1) == -1)
        {
            printf("Failed to write\n");
            return 4;
        }
        printf("String sent\n");

        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char str[200];
        int n;
        wait(NULL);

        // read strlen
        if (read(fd[0], &n, sizeof(int)) == -1)
        {
            printf("Failed to read\n");
            return 5;
        }

        // read string
        if (read(fd[0], str, sizeof(char) * n) == -1)
        {
            printf("Failed to read\n");
            return 6;
        }

        printf("String read: %s\n", str);

        close(fd[0]);

        wait(NULL);
    }
    return 0;
}