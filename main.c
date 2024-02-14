#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void runChild(int childNum, int programNum) {

    char programName[10];
    sprintf(programName, "test%d", programNum); // simulates child processes running a program

    printf("Started child %d with pid %d\n", childNum, getpid());

    execlp(programName, programName, NULL); // each child process starts a sample program

    perror("execlp"); 
    exit(EXIT_FAILURE); // exit
}

int main() {
    
    pid_t parentPid = getpid(); // one additional child process
    printf("Parent pid is %d\n", parentPid);

    
    for (int childNum = 1; childNum <= 6; ++childNum) { // using a loop to generate a constant number of child processes
        pid_t pid = fork();

        if (pid == -1) {

            perror("Fork failed");
            exit(EXIT_FAILURE); //exit

        } else if (pid == 0) {

            runChild(childNum, childNum % 5 + 1);  // each child starts one of the sample programs
            exit(EXIT_SUCCESS);
        }
    }

    
    for (int i = 0; i < 6; ++i) {
        int status;
        pid_t finishedChild = waitpid(-1, &status, 0); // the parent process waits for all child processes to complete

        
        if (WIFEXITED(status)) { // distinguishes between individual child processes as they complete their execution.
            printf("Child %d (PID %d) finished\n", i + 1, finishedChild);
        }
    }

    printf("Parent process exiting\n");

    
    pid_t pid;
    pid = fork(); // create a child process

    if (pid < 0) { 

        fprintf(stderr, "Fork failed"); // fork fail
        return 1;

    } else if (pid == 0) { 

        printf("Child: listing of current directory\n\n");
        execlp("/bin/ls", "ls", NULL);

    } else { 

        printf("Parent: waits for child to complete\n\n"); // parent process�wait for child to complete
        wait(NULL);
        printf("Child complete\n\n");

    }

    return 0;
}
