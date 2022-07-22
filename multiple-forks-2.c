// n processes ?!
// n*n file descriptors
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PROCESS_NUM 10
int main(int argc, char *argv[])
{
    int pids[PROCESS_NUM];
    int pipes[PROCESS_NUM + 1][2];
    int i;
    for (i = 0; i < PROCESS_NUM + 1; i++)
    {
        if (pipe(pipes[i]) < 0)
        {
            printf("failed to create pipe\n");
            return 1;
        }
    }
    for (i = 0; i < PROCESS_NUM; i++)
    {
        pids[i] = fork();
        if (pids[i] < 0)
        {
            printf("failed to fork\n");
            return 2;
        }
        if (pids[i] == 0)
        {
            // child process
            int j;
            for (j = 0; j < PROCESS_NUM; j++)
            {
                if (i != j)
                {
                    close(pipes[j][0]);
                }
                if (i + 1 != j)
                {
                    close(pipes[j][1]);
                }
            }
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) < 0)
            {
                printf("read failed\n");
                return 3;
            }
            printf("%d got %d\n", i, x);
            x++;
            if (write(pipes[i + 1][1], &x, sizeof(int)) < 0)
            {
                printf("write failed\n");
                return 4;
            }
            printf("%d sent %d\n", i, x);
            close(pipes[i][0]);
            close(pipes[i + 1][1]);

            return 0;
        }
    }

    // main process
    int x;
    printf("Enter number\n");
    scanf("%d", &x);
    printf("Main sent %d\n", x);
    int j;
    for (j = 0; j < PROCESS_NUM; j++)
    {
        if (j != PROCESS_NUM)
        {
            close(pipes[j][0]);
        }
        if (j != 0)
        {
            close(pipes[j][1]);
        }
    }

    if (write(pipes[0][1], &x, sizeof(int)) < 0)
    {
        printf("write failed\n");
        return 5;
    }
    if (read(pipes[PROCESS_NUM][0], &x, sizeof(int)) < 0)
    {
        printf("read failed\n");
        return 6;
    }
    printf("Result: %d\n", x);
    close(pipes[0][1]);
    close(pipes[PROCESS_NUM][0]);
    for (i = 0; i < PROCESS_NUM; i++)
    {
        wait(NULL);
    }

    return 0;
}