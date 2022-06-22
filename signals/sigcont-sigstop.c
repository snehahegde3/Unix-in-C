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
            printf("output\n");
            usleep(50000);
        }
    }

    else
    {
        // stop before taking input
        kill(pid, SIGSTOP);
        int t;
        do
        {
            // input time for execution
            printf("Time in secs for sexecution: ");
            scanf("%d", &t);
            // if t is -ve it goes on for max_int time
            if (t > 0)
            {
                // continues for t secs, stoop
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }

        } while (t > 0);

        wait(NULL);
    }
}