#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/*
the user is asked a question and is expected to answer
if takes more than 5 seconds, we signal
*/

// global because we are checking it in the handling function
int x = 0;
void handle_sigusr1(int sig)
{
    if (x == 0)
    {
        printf("\n[HINT] Remember that multiplication is repetitive addition\n");
    }
}
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
        // child process

        sleep(5);
        // after 5 seconds, send signal
        kill(getppid(), SIGUSR1);
    }

    else
    {
        // parent process

        // to handle the signal instead of using the default action for the specified signals,
        struct sigaction sa;
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);

        printf("What is 3 * 5 ? : ");
        scanf("%d", &x);
        if (x == 15)
        {
            printf("Right\n");
        }
        else
        {
            printf("Wrong\n");
        }
        wait(NULL);
    }
    return 0;
}