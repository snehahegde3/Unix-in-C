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
    //open fifo 
    int fd = open("sum", O_RDONLY);
    if(fd==-1){
        return 1;
    }

    int arr[5];
    int i;
    int sum = 0;
    
    //reading from fifo
    //read from fifo buffer as a single element 
    // for(int i=0;i<5;i++){
    //     if(read(fd, &arr, sizeof(int))==-1){
    //         return 2;
    //     }
    //     printf("Read %d\n", arr[i]);
    // }
    if(read(fd, arr, sizeof(int)*5)==-1){
        return 2;
    }

    for(int i=0;i<5;i++){
        sum+=arr[i];
    }
    printf("Sum: %d\n", sum);

    close(fd);

    //opening fifo again to send the sum back 
    int fd1 = open("sum", O_WRONLY);
    if(fd1==-1){
        return 1;
    }

    if(write(fd1, &sum, sizeof(int))==-1){
        return 2;
    }
    printf("Sum sent back\n");

    close(fd1);

    


    //execte sum_read and sum_write smiultaeosly
    
    return 0;
}