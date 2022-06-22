#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        while (1)
        {
            printf("This goes on indefinately\n");
            usleep(50000);
        }
    }

    else
    {
        // signals control the processes at a granular level
        //  wait one second before killing the child process
        sleep(1);
        kill(pid, SIGKILL); // sends signal to terminate
        wait(NULL);
    }
}