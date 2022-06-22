#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

/*sending and receiving batches of data through fifo*/
//mkfifo sum 
int main(int argc, char* argv){
    int arr[5];
    srand(time(NULL));
    int i;
    for(int i=0;i<5;i++){
        arr[i] = rand() % 10;
        printf("Generated: %d\n", arr[i]);
    }

    //open fifo 
    int fd = open("sum", O_WRONLY);
    if(fd==-1){
        return 1;
    }
    
    //writing into fifo
    // for(int i=0;i<5;i++){
    //     if(write(fd, &arr[i], sizeof(int))==-1){
    //         return 2;
    //     }
    // }


    //using entire array insread of loop
    //arr evaluates to address of first element of array     
    if(write(fd, arr, sizeof(int) * 5)==-1){
        return 2;
    }
    close(fd);

    //sum gotten back by the other program 
    int sum;


    int fd1 = open("sum", O_RDONLY);
    if(fd1==-1){
        return 1;
    }

    if(read(fd1, &sum, sizeof(int))==-1){
        return -2;
    }
    printf("Sum gotten back: %d\n", sum);

    close(fd1);
    
    return 0;
}