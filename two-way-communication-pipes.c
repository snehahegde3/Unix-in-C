#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/*
program to generate a number,
send it through a pipe to another process, which multiplies it by 10
this is sent back to the original process
*/

/*
note that this cannot be done using a single pipe
data can be read before being written and vice versa
we cannot have a pipe that both sends data and recieves data from the same process
*/
int main(int argc, char *argv)
{
    int p1[2] /*child to parent*/, p2[2] /*parent to child*/;
    if (pipe(p1) == -1)
    {
        printf("Failure while pipe()\n");
        return 1;
    };
    if (pipe(p2) == -1)
    {
        printf("Failure while pipe()\n");
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
        sleep(2);
        // child process

        close(p1[0]);
        close(p2[1]);

        // read the value sent from parent
        int x;
        if (read(p2[0], &x, sizeof(x)) == -1)
        {
            printf("Failed to read\n");
            return 3;
        }
        printf("Recieved: %d\n", x);

        // multiply by 10
        x *= 10;

        sleep(3);

        // send back the new value to parent
        if (write(p1[1], &x, sizeof(x)) == -1)
        {
            printf("Failed to write\n");
            return 4;
        }
        printf("Responded: %d\n", x);

        close(p1[1]);
        close(p2[0]);
    }
    else
    {
        sleep(1);
        // parent process
        // generate number and send o child

        close(p1[1]);
        close(p2[0]);

        // srand mported from time.h
        srand(time(NULL));
        int y = rand() % 10 + 1;
        if (write(p2[1], &y, sizeof(y)) == -1)
        {
            printf("Failed to write\n");
            return 5;
        }
        printf("Sent: %d\n", y);

        sleep(5);

        // read the response from child
        if (read(p1[0], &y, sizeof(y)) == -1)
        {
            printf("Failed to read\n");
            return 6;
        }
        printf("Response: %d\n", y);

        close(p1[0]);
        close(p2[1]);
    }
    wait(NULL);
    return 0;
}