#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
/*
#include "test1.c"
#include "test2.c"
#include "test3.c"
#include "test4.c"
#include "test5.c"
*/

void runChild(int childNum, int programNum) { // simulates child processes running a program
        
    printf("Started child %d with pid %ld\n", childNum, (long)getpid());

    if (programNum == 1){
            //execlp
            execlp("./test1", "test1", NULL);
            if (execlp("./test1", "test1", NULL) == -1){
                perror("EXECLP ERROR!!!!!!!");
            }
            printf("programNum is: %d\n", programNum);
            printf("child is: %d\n", childNum);
            printf("should be executing test.1\n");
        }
        else if (programNum == 2){
            //execlp
            printf("programNum is: %d\n", programNum);
            printf("child is: %d\n", childNum);
            printf("should be executing test.2\n");
            printf("\n");
        }
        else if (programNum == 3){
            //execlp
            printf("programNum is: %d\n", programNum);
            printf("child is: %d\n", childNum);
            printf("should be executing test.3\n");
            printf("\n");
        }
        else if (programNum == 4){
            //execlp
            printf("programNum is: %d\n", programNum);
            printf("child is: %d\n", childNum);
            printf("should be executing test.4\n");
            printf("\n");
        }
        else if (programNum == 0){
            //execlp
            printf("programNum is: %d\n", programNum);
            printf("child is: %d\n", childNum);
            printf("should be executing test.5\n");
            printf("\n");
        }

    char programName[10];
    //sprintf(programName, "test%d", programNum);

    //printf("Started child %d with pid %ld\n", childNum, (long)getpid());

    //if (execlp(programName, programName, NULL) == -1) { // executes the specified program
    //if (execlp("test1", "test1", NULL) == -1) { // executes the specified program

        //perror("execlp. the error printing is here");
        exit(EXIT_FAILURE);

    }

int main(char argc, char **argv) {

    int userNum;
    userNum = atoi(argv[1]); //user input of no.of child process in the userNum variable

    printf("Program argv[0] is: %d\n", userNum);
    pid_t parentPid = getpid();
    printf("Parent pid is %ld\n", (long)parentPid);

    
    for (int childNum = 1; childNum <= userNum; ++childNum) { 

        pid_t pid = fork();

        
        if (pid == -1) { // fork failure check (not necessary but helpful)

            perror("Fork failed");
            exit(EXIT_FAILURE);

        } else if (pid == 0) {
        
            runChild(childNum, childNum % 5); 
            exit(EXIT_SUCCESS); // exit function for the child process after the program is ran
        }
    }

   
    for (int i = 0; i < userNum; ++i) { // waits for child processes to complete

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

//execlp(".test1", "test1", "fork 1", NULL);

/*
TODO: 
to call the test files
if userNum = 6:
    child 1 and 6 executes test 1 and child 2-> test2, etc
add printf("Child ", include which child and PID, " finished");
printf("Child %d (PID %ld) finished\n", i + 1, (long)finishedChild);
*/

