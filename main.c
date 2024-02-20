#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void runChild(int childNum, int programNum) { // simulates child processes running a program
    
    char *args[]= {"./test1", "./test2", "./test3", "./test4", "./test5",NULL};
    printf("Started child %d with pid %ld\n", childNum, (long)getpid());

    if (programNum == 1){
        if (execv(args[0], args) == -1){
            perror("EXECV error!!!");
            }
            else (execve(args[0], args, NULL));
            exit(0);
        }

    else if (programNum == 2){
        if (execv(args[1], args) == -1){
            perror("EXECV error!!!");
        }
        else (execve(args[1], args, NULL));
            exit(0);
    }

    else if (programNum == 3){
        if (execv(args[2], args) == -1){
            perror("EXECV error!!!");
        }
        else (execve(args[2], args, NULL));
        exit(0);
    }

    else if (programNum == 4){
        if (execv(args[3], args) == -1){
            perror("EXECV error!!!");
        }
        else (execve(args[3], args, NULL));
        exit(0);
    }

    else if (programNum == 0){
        if (execv(args[4], args) == -1){
            perror("EXECV error!!!");
        }
        else (execve(args[4], args, NULL));
        exit(0);
    }
    exit(EXIT_FAILURE);
}

int main(char argc, char **argv) {

    int userNum;
    userNum = atoi(argv[1]); //user input of child processess

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





    //dont think we need the following!!!
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