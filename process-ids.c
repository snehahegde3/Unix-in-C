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
    
    printf("Current ID : %d, Parent ID: %d\n", getpid(), getppid());

    //res in here gives the ID of the process the parent process is waiting for
    int res = wait(NULL);
    if(res == -1)
    {
        printf("No children process to wait for\n");
    }
    else{
        printf("%d finished execution\n", res);
    }

    return 0;
}

