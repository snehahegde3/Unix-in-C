#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
    int id = fork();
    if(id == 0)
    {
        //child process waits while the parent finishes execution
        sleep(1);
    }
    //so when we print the parent ID of the child process whos parent has already terminated
    //we get a different ID that the parent ID it was created from 
    //OS assignes a different ID to an orphan process
    printf("Current ID : %d, Parent ID: %d\n", getpid(), getppid());
    return 0;
}

