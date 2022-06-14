#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// contains all the errors
#include <errno.h>

/*

                 ________________           ________________
                |               |          |       z       |
                |    id1 = x    |          |    id1 = x    |
                |    id2 = z    |----------|    id2 = 0    |
                |_______________|          |_______________|
                        |
                        |
                 _______|________
                |       x       |
                |    id1 = x    |
                |    id2 = z    |
                |_______________|
                        |
                        |
                 _______|________
                |       y       |
                |    id1 = 0    |
                |    id2 = 0    |
                |_______________|





*/

int main(int argc, char *argv[])
{
    // twice fork results in four processes
    int id1 = fork();
    int id2 = fork();
    if (id1 == 0)
    {
        if (id2 == 0)
        {
            // child of child process
            printf("Process y. ID: %d. Parent ID: %d\n", getpid(), getppid());
        }
        else
        {
            printf("Process x. ID: %d. Parent ID: %d\n", getpid(), getppid());
        }
    }
    else
    {
        if (id2 == 0)
        {
            printf("Process z. ID: %d. Parent ID: %d\n", getpid(), getppid());
        }
        else
        {
            printf("Parent process. ID: %d. Parent ID: %d\n", getpid(), getppid());
        }
    }

    // waiting here for the child processes becomes hard
    // as wait only waits for one process
    // waiting for one process and terminating of the parent leads to the other children turning into orphans
    // and here we have three
    while (wait(NULL) != -1 /*if theres nothing to wait for*/ || errno != ECHILD /*No child processes*/)
    {
        // this should be printed three times on the screen as we have three child processes the parent has to wait for
        printf("Waited for a child to finish\n");
    }
    return 0;
}
