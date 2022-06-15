/*
practical use case for pipe + fork
sum of all elements in na array by dividing it into three
processes do 1/3rd of the work
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int fd[2];
    int start, end;
    int size = sizeof(arr) / sizeof(arr[0]);
    if (pipe(fd) == -1)
    {
        printf("Error occured while oepening the pipe\n ");
        return 1;
    }

    int id1 = fork();
    int id2 = fork();
    if (id1 == -1)
    {
        printf("Error while fork\n");
        return 1;
    }
    if (id2 == -1)
    {
        printf("Error while fork\n");
        return 1;
    }
    if (id1 == 0)
    {
        if (id2 == 0)
        {
            start = 0;
            end = start + size / 3;
        }
        else
        {
            start = size / 3;
            end = start + size / 3;
        }
    }
    else
    {
        if (id2 == 0)
        {
            start = (2 * size) / 3;
            end = size;
        }
        else
        {
            wait(NULL);
        }
    }
    int sum = 0;
    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }
    printf("Calculated partial sum: %d\n", sum);

    if (id1 == 0)
    {
        if (id2 == 0)
        {
            close(fd[0]);
            if (write(fd[1], &sum, sizeof(int)) == -1)
                return 3;
            close(fd[1]);
        }
        else
        {
            int temp;
            if (read(fd[0], &temp, sizeof(int)) == -1)
                return 4;
            close(fd[0]);
            sum += temp;
            if (write(fd[1], &sum, sizeof(int)) == -1)
                return 5;
            close(fd[1]);
        }
    }
    else
    {
        if (id2 == 0)
        {
            int temp;
            close(fd[1]);
            if (read(fd[0], &temp, sizeof(int)) == -1)
                return 4;
            close(fd[0]);
            sum += temp;
            printf("Total sum: %d\n0", sum);
        }
        else
        {
            wait(NULL);
            // wait for the child process to finish half of the summation
        }
    }
    return 0;
}