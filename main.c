#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void runChild(int childNum, int programNum) { // simulates child processes running a program

    char programName[10];
    sprintf(programName, "test%d", programNum);

    printf("Started child %d with pid %ld\n", childNum, (long)getpid());

    
    if (execlp(programName, programName, NULL) == -1) { // executes the specified program

        perror("execlp");
        exit(EXIT_FAILURE);

    }
}

int main(char argc, int **argv) {

    printf("argv value is\n:", argv[0]);
    pid_t parentPid = getpid();
    printf("Parent pid is %ld\n", (long)parentPid);

    
    for (int childNum = 1; childNum <= 6; ++childNum) { // 6 child processes

        pid_t pid = fork();

        
        if (pid == -1) { // fork failure check (not necessary but helpful)

            perror("Fork failed");
            exit(EXIT_FAILURE);

        } else if (pid == 0) {

            runChild(childNum, childNum % 5 + 1);
            exit(EXIT_SUCCESS); // exit function for the child process after the program is ran
        }
    }

   
    for (int i = 0; i < 6; ++i) { // waits for child processes to complete

        int status;
        pid_t finishedChild = waitpid(-1, &status, 0);

        
        if (WIFEXITED(status)) { // makes sure the child process wwas successfully exited

            printf("Child %d (PID %ld) finished\n", i + 1, (long)finishedChild);

        }
    }

    printf("Parent process exiting\n");

    
    pid_t pid = fork(); // another child process is created

    
    if (pid == -1) { // fork failure check

        perror("Fork failed");
        return 1;

    } else if (pid == 0) {

        printf("Child: listing of the current directory\n\n");
        execlp("/bin/ls", "ls", NULL); // runs 'ls' command in the child process
        perror("execlp"); // execlp failure check
        exit(EXIT_FAILURE); // exits if execlp fails

    } else {

        printf("Parent: waits for child to complete\n\n");
        wait(NULL); // waits for child process to finish
        printf("Child complete\n\n");

    }

    return 0; // Exit the main program
}