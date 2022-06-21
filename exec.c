#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//for windows, 
// #include <process.h>
//for linux
#include <unistd.h>

int main(int argc, char *argv){
    _execl(/*exe, path of exe, argument to exe, NULL*/);
    return 0;
}