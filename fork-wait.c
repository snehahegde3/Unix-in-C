#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // if the parent doesnt wait for the child like they usually run concurrently
    // the numbers ar not printed in order

    int id = fork();
    int n;
    if (id == 0)
    {
        n = 1;
    }
    else
    {
        n = 6;
    }
    if (id != 0)
    {
        // waits for the child process to complete
        // placed here as we only wait if its the parent process
        wait();
    }
    int i;
    for (i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        // clear (or flush) the output buffer and move the buffered data to console
        fflush(stdout);
    }
    if (id != 0)
    {
        printf("\n");
    }
    return 0;
}
