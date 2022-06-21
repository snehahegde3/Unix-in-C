#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for windows,
// #include <process.h>
// for linux
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv, char *envp[])
{
    // exec overwrites everything not only memory, the entire execution

    // once we call this we are no longer in our old program

    // execl takes a list of arguements
    //  execl("C:\\Windows\\System32\\ping.exe", "C:\\Windows\\System32\\ping.exe", "google.com", NULL);

    // execlp uses path variables to find ping
    // execlp("ping", "ping", "google.com", NULL);

    // execvp takes an array
    char *arr[] = {
        "ping", "google.com", NULL};
    // execvp("ping", arr);

    // execvpe takes environement
    char *env[] = {
        "TEST=enivironment variable",
        NULL};
    execvpe("ping", arr, env);

    // runs when ping fails
    int err = errno;
    printf("Ping finished executing\n");

    return 0;
}