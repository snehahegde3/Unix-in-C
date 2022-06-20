#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>


/*
pipes can only be used by files in the same heirarcy 
file descriptors when forked, are copied over to the child process 
and close on their own

Fifos: files to which you can read or write from any process
a fifo is a name pipe 
create a fifo by mkfifo
*/
int main(int argc, char* argv){
    if(mkfifo("myfifo", 0777/*permission: read from and wrote to by anybody*/)==-1){
        if(errno != EEXIST /*when fifo alrady exists*/){
            printf("Could not create fifo\n");
            return 1;
        }
        else{
            printf("fifo already exists\n");
        }
        
    }


    //open found in fcntl lib
    //oepening in write only
    printf("Opening...\n");
    int fd = open("myfifo", O_WRONLY);
    printf("Opened!\n");
    int x = 79;
    if(write(fd, &x, sizeof(x))==-1){
        return 2;
    }
    printf("Written\n");
    close(fd);
    printf("Closed\n");
    /*
    the above code just open the fifo and hangs there
    this is because ... for fifos, 
    opeening the read or write end of the fifo blocks
    until the other end also oepened by anoter process or thread
    openeing the mkfifo by the cat command in another terminal solves this
    
    similarly if we read from fifo without anyone writing to it, 
    it blocks
    */

    return 0;
}