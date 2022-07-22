#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid1 = fork();
    if (pid1 < 0)
    {
        printf("failed to fork\n");
        return 1;
    }
    if (pid1 == 0)
    {
        sleep(4);
        printf("Finished execution %d\n", getpid());
        return 0;
    }

    int pid2 = fork();
    if (pid2 < 0)
    {
        printf("failed to fork\n");
        return 0;
    }
    if (pid2 == 0)
    {
        sleep(1);
        printf("Finished execution %d\n", getpid());
        return 0;
    }

    int pid1_res = waitpid(pid1, NULL, 0);
    printf("Waited for %d\n", pid1_res);
    int pid2_res = waitpid(pid2, NULL, 0);
    printf("Waited for %d\n", pid2_res);

    // pid < -1 waits fpr group
    // pid = -1 waits for any
    return 0;
}