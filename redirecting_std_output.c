#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
File descriptors:
They are unique across a file.
They are things we can read from or write to.
fd 0 is automatically linked to stdin
fd 1 is automatically linked to stdout
fd 2 is automatically linked to stderr
lets take fd 3 linked to pingResults
this has to be then directed to stdout
*/

int main(int *argc, char *argv)
{
    int pid = fork();
    if (pid == -1)
    {
        printf("Failed fork()\n");
        return 1;
    }

    if (pid == 0)
    {
        // child

        // open the file to write into
        int file = open("pingResults.txt", O_WRONLY | O_CREAT /*creates file if doesnt exist*/, 0777 /*permissions*/);
        if (file == -1)
        {
            return 2;
        }
        // dup duplicates by adding another fd linked to specified file
        // dup2 links the fd specified to the specified file
        // in this case, the stdout (fd - 1)
        printf("fd to pingResults: %d\n", file);
        dup2(file, STDOUT_FILENO);
        close(file);

        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        if (err == -1)
        {
            printf("Could not find program to execute\n");
        }
        printf("This will not show up on theterminal\n");
    }
    else
    {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus))
        {
            int statusCode = WEXITSTATUS(wstatus);
            if (statusCode == 0)
            {
                printf("Success\n");
            }
            else
            {
                printf("Failure with status code %d\n", statusCode);
            }
        }
    }
    return 0;
}