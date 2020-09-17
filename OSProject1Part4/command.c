#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    /*Write a program to take a UNIX command from the command line
    and fork() a child to execute it. The command can be a simple
    command like: $ls or $ps, Or it can be a command with options such as
    $ls -t -l. Use argc and argv[] in the main function to pass parameters.
    When the child process is executing the command, the parent process
    simply waits for the termination of the child process. The process
    id of the parent and the child should be printed out using getpid() and
    getppid() functions. */

    int pid;
    pid_t parent, child;
    pid=fork();
    if(pid<0)
    {
       printf("error........\n");
    }
    else if(pid==0) /*child*/
    {
        execl("/usr/bin/ls",argv[1],argv[2],argv[3],NULL);
    }
    else /*parent*/
    {
        wait(NULL);
        child=getpid();
        parent=getppid();

        printf("\nThe child process id: %d\n",child);
        printf("The process id of parent function: %d\n",parent);
        exit(0);
    }


    return 0;
}
