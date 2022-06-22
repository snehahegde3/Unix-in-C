#include <stdio.h>
#include <stdlib.h>

/*
"Bringing into the background" means stopping a process (SIGSTOP)
When we hit ctrl+z, it stops the process but this doesnt mean its termination

Termination means that the process has reached and exit status, all the memory it had been occupying has now been freed

Whereas, stopping is more like pausing it, it is stuck in a line of code and waits for a signal to continue
sigcont did this after a sigstop

"Bringing into foreground" means continuing the process stopped (SIGCONT)
*/

int main(int argc, char *argv[])
{
    int x;
    printf("Input number: ");
    // If we Ctrl+z here, the terminal sends a SIGTSTP() signal to this main process and turns into a background process.
    // To turn into a foreground process again, we type the comand fg <id>. In this case, fg is enough
    // It sends a SIGCONT signal internally to continue the process execution.

    scanf("%d", &x);
    printf("Result: %d\n", x * 5);
    return 0;
}