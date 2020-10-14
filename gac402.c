#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

/*
* This program is to take a command from the user and execute that command using
* fork and exec if it is not a built-in command (print, exit, and printid).
* Author: Gabby Clavell
*/
int main (int argc, char * argv[], char * envp[]){

    while(1){

        char path[]= "/bin/";    //set path at bin
        char cmd[10];      //user input
        char fullPath[10];    //full file path
        int child_status;

        printf("lab1> ");                    //print shell prompt

        fgets(cmd, 10, stdin);           // do fgets() or scanf

        cmd[strlen(cmd)-1] = '\0';      // get rid of the \n character at the end

        printf( "Parent Process %d\n", (int) getpid());

    if (strcmp(cmd, "exit") == 0) {
        exit(0);
    }

    else if (strcmp(cmd, "greet") == 0) {
        printf("Hello\n");

    }
    else if (strcmp(cmd, "printid") == 0) {
        printf("%d", getpid());

     }
    // if the string entered by the user is a built-in command
        // check the string and based on it, do the corresponding tasks
    else {
        //strcpy(fullPath, path);
        strcat(fullPath, path);
        strcat(fullPath, cmd);
        //fullPath[strlen(fullPath)-1] = '\0';

        //printf("%s\n", fullPath); // checking to see if it is added properly

        char *argv[] = {cmd, NULL};

        pid_t child = fork();    //fork child

        if(child == 0) {             //Child
            printf( "Child process %d will execute the command %s\n", (int) getpid(), cmd);
            // add in
            //execve - use string entered by user to transform the child process to the
            // new process inside will be execve(&fullPath, progname, NULL);

            // if execution of the child process reaches this point, it means execve failed.
            // in that case, print "Command Not Found" and exits
                //return -1; // error
            if (execve(fullPath, argv, NULL)) {
                printf("Command Not Found\n");
                exit(-11);
            }
        }
    }

    // find the result from executing the command
    wait(&child_status);

    //return
    return(0);
    }
}
