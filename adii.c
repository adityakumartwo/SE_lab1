#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
    FILE *wfp, *rfp;
    char line[81];

    // Open a pipe to "cat" for writing (P2)
    wfp = popen("cat", "w");
    if (wfp == NULL) {
        perror("popen cat");
        exit(1);
    }

    // Open a pipe from "nl" for reading (P3)
    rfp = popen("nl", "r");
    if (rfp == NULL) {
        perror("popen nl");
        exit(1);
    }

    printf("Type lines (Ctrl+D to end):\n");

    // Main loop: read user input, send it to cat, then read from nl
    while (fgets(line, sizeof(line), stdin) != NULL) {
        // Write user input into cat
        fputs(line, wfp);
        fflush(wfp);

        // Read nl's output (line-numbered) and print it
        if (fgets(line, sizeof(line), rfp) != NULL) {
            printf("%s", line);
        }
    }

    // Close pipes
    pclose(wfp);
    pclose(rfp);

    printf("\nProgram terminated.\n");
    exit(0);
}


/*

Explaination

**************************
1. Purpose

We want to build a pipeline of processes using the popen() system call instead of manually using pipe() and fork().
P2 → executes the command cat
We send user input to it.
P3 → executes the command nl
It reads the output from cat, numbers the lines, and prints them.

Data Flow: User input → cat (P2) → pipe → nl (P3) → Screen
The program should keep working until the user presses Ctrl+D (end of file).

*************************
2. Key Functions Used

popen(command, mode)
Starts a process running the given command.
Creates a pipe connected to that process.
Returns a file pointer.
If mode = "w" → we can write into the process’s stdin.
If mode = "r" → we can read from the process’s stdout.
pclose()
Closes the pipe and waits for the process to finish.

***************************
3. Program Behavior
Step 1: Open Pipes
wfp = popen("cat", "w");   // For writing into cat’s stdin
rfp = popen("nl", "r");    // For reading from nl’s stdout

Step 2: Read from User
while (fgets(line, sizeof(line), stdin) != NULL) {
    ...
}
Reads a line typed by the user.
Stops when Ctrl+D is pressed (EOF).

Step 3: Send to cat
fputs(line, wfp);
fflush(wfp);
The line is sent into the cat process.
fflush() makes sure it is immediately written.

Step 4: Get from nl
if (fgets(line, sizeof(line), rfp) != NULL) {
    printf("%s", line);
}
Reads the output of nl.
Prints it to the screen.

Step 5: Close Pipes
pclose(wfp);
pclose(rfp);
Cleanly closes the pipes after the user exits with Ctrl+D.

**************************
Summary

1. popen() allows us to run existing commands (cat, nl) and connect to them using pipes.
2. We can use "w" mode to write into a command’s stdin.
3. We can use "r" mode to read from a command’s stdout.
4. The program structure mimics P2 → P3 pipeline without manually handling fork() and pipe().
5. The program terminates cleanly when the user presses Ctrl+D.

*/