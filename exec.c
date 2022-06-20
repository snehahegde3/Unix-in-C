#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int *argc, char* argv){
    
    /*
    Not only does exec replace specifid but it replaces entire process
    all memory is replaced by its own memory 
    exectution line replaced with its own execution line
    So, to continue execution after, we create a new process and them exec 
    */
    // execlp("ping", "ping", "-c", "3", "google.com", NULL);

    int pid = fork();
    if(pid == -1){
        printf("Failed fork()\n");
        return 1;
    }

    /*
    If exec is called on the parent process,it gets replaced. 
    It cant wait anymore for the child process
    child turns into a zombie process, its memory is gonna be freed
    So, call the exec on child while parent waits for it to finish 
    */

    if(pid == 0){
        //child
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
        printf("This will not show up on theterminal\n");
    }
    else{
        wait(NULL);
        printf("Postprocessing\n");
        printf("Succes\n");
    }
    return 0;
}