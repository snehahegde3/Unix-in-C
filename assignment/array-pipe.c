#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h> //srand
/*
well have two processes.

Child will generate random numbers and send to parent

Parent sums the numbers and print result
 */
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
        // child
        // close read end
        close(fd[0]);
        int n, i;
        int arr[10];
        srand(time(NULL));
        n = rand() % 10 + 1;
        printf("Generated\n");
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 11;
            printf("%d\n", arr[i]); // 0-10 inclusive
        }

        // send the number of elements before sending the array
        // otherwise the parent cant know
        if (write(fd[1], &n, sizeof(int)) == -1)
        {
            printf("Failed to write\n");
            return 3;
        }

        printf("Sent n = %d\n", n);

        // write into write end
        if (write(fd[1], arr, sizeof(int) * n) == -1)
        {
            printf("Failed to write\n");
            return 4;
        }
        printf("Array sent\n");

        close(fd[1]);
    }
    else
    {
        // close write end
        close(fd[1]);
        int arr[10];
        int n;
        wait(NULL);

        // read the number if array elements first, thens the array
        if (read(fd[0], &n, sizeof(int)) == -1)
        {
            printf("Failed to read\n");
            return 5;
        }
        printf("Received n: %d\n", n);

        // read array
        if (read(fd[0], arr, sizeof(int) * n) == -1)
        {
            printf("Failed to read\n");
            return 6;
        }
        printf("Received\n");

        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += arr[i];
        }
        printf("Reusult of sum: %d\n", sum);

        close(fd[0]);

        wait(NULL);
    }
    return 0;
}