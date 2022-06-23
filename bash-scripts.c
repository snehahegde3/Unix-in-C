#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/*
In the redirection of standard output, it was observed that we cannot run bash scripts through exec

What when we want to execute "ping -c 5 google.com | grep rtt"
Here ther are teo programs:  -----                   ----
Linked through "|" operator
The output of the left program i.e. ping is routed through the pipe to the second program grep

ping -c 5 google.com | grep rtt
----                ^  ---- ^
   |__stdout_______| |stdin|

ping is writing its stdout to grep not stdout
stdin of grep is set to be in this pipe
so it takes stdout from ping as input

The commands after "|" are only understood by ping

To simulate this,
                 ________________           ________________
                |               |          |               |
                |               |----------|      ping     |
                |_______________|          |_______________|
                        |        \       / / /
                        |         \    / / /
                 _______|________  \ / / /
                |               |  / / /
                |      grep     |/ v /
                |_______________|


*/

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        printf("Failure while pipe()\n");
        return 1;
    }

    int pid1 = fork();
    if (pid1 == -1)
    {
        printf("Failure while fork()\n");
        return 2;
    }

    if (pid1 == 0)
    {
        // child process (ping)
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        // as fd[1] remains open even thos weve duplicated it
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }

    int pid2 = fork();
    if (pid2 == -1)
    {
        printf("Failure while fork\n");
        return 3;
    }

    if (pid2 == 0)
    {
        // child (grep)
        // grep is waiting to raed from the reading end
        // from the ping
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);

        execlp("grep", "grep", "rtt", NULL);
    }
    // grep keeps reading input but doesnt know when to stop waiting
    // closes only when all the writers are closed
    // the main process still has write end open for the file so it waits

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}