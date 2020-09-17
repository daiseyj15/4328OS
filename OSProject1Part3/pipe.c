#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*Write a c program to set up a parent-TO-child pipe; the parent
should 'exec' to perform a "pre" process and its output should be
connected to the pipe connected to the child, which should 'exec' to
perform a "sort" process.*/

int main(int argc,char *argv[])
{
    int fd[2];
    int pid;
    pipe(fd);
    pid=fork();

    if(pid<0)
    {
       printf("error........\n");
    }
    else if(pid==0)/*child sort.c*/
    {
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        execl("./a.out","./a.out",NULL);
    }
    else/*parent pre.c*/
    {
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        execl("./pre","./pre",NULL);
    }

    return 0;
}
