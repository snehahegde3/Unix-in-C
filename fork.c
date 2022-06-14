#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // forking the execution line when called once
    //
    // -------> fork()  parent ----------> fork()
    //
    //                  child  ----------> fork()

    // forking the execution line when called twice
    // -------> fork()  parent ----------> fork() paernt ---------->
    //
    //                                            child2 ---------->
    //
    //                  child1 ----------> fork() child1 ---------->
    //
    //                                            child3 ---------->
    int id = fork();

    if (id == 0)
    {
        // returns 0 to the child process on successful creation
        printf("Hello from child process with id: %d\n", id);
    }
    else
    {
        // returns the id of the child process on successful creation
        printf("Hello from parent process with id: %d\n", id);
    }
    return 0;
}
