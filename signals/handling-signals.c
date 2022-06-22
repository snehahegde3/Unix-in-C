#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
/*changing the way we handle signals*/

// function that is called when we get a signal
void handle_sigtstp(int sig)
{
    printf("Stop not allowed\n");
}

// since fg calls sigcont
void handle_sigcont(int sig)
{
    printf("Input number: \n");
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    struct sigaction sa;
    sa.sa_handler = &handle_sigcont;
    // only for SIGTSTP
    // as were using a caombination of SIGTSTP and scanf
    sa.sa_flags = SA_RESTART;
    // sigaction(SIGTSTP, &sa, /*old sigaction*/ NULL);
    sigaction(SIGCONT, &sa, /*old sigaction*/ NULL);

    // // does the same thing
    // signal(SIGTSTP, &handle_sigstrp);

    // sigcont continues the execution after handling the signal
    int x;
    printf("Input number: ");
    scanf("%d", &x);
    printf("Result: %d\n", x * 5);
    return 0;
}