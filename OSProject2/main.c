#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
char *argv[20], buf[80], n, *p, input[40], output[40];

int m, status, inword, continu, x, startposition[10], pipes, inputflag;
pid_t pid;
int pipespp, outputflag, processes,r_fd[2],l_fd[2],y,w;


while(1) {

inputflag=0;
outputflag=0;
pipes=0;
startposition[0]=0;
inword = 0;

p = buf;

m = 0;

continu=0;



printf( "\nshhh> ");

while ( ( n = getchar() ) != '\n'  || continu ) {

	if ( n ==  ' ' ) {

	    if ( inword ) {

		inword = 0;

		*p++ = 0;

	    }

	}

	else if ( n == '\n' ) continu = 0;

	else if ( n == '\\' && !inword ) continu = 1;

	else {

	    if ( !inword ) {

		 inword = 1;

		 argv[m++] = p;

		 *p++ = n;

	     }

	     else

		 *p++ = n;

	}

}

*p++ = 0;

    x=m;
argv[m] = 0;/*puts zero at end of array*/



if ( strcmp(argv[0],"exit") == 0 ) exit (0);

/* Dont change above this */

    while(x > 0)
    {
        /*we got to save the input or output file name*/
        if( strcmp(argv[x],">") == 0 )
        {
            argv[x]=0;
            strcpy(output,argv[x+1]);
            outputflag=3;
        }
        /*we got to save the input or output file name*/
        if( strcmp(argv[x],"<") == 0 )
        {
            argv[x]=0;
            strcpy(input,argv[x+1]);
            inputflag=2;
        }
        if(strcmp(argv[x],"|")==0)
        {
            pipes++;
            argv[x]=0;
            startposition[pipes]=(x+1);
        }
        x--;
    }

    /* pipes+1 processes */
    processes=pipes+1;
    y=pipes+1;
    pipespp=pipes;
    /*use a flag to know if you have redirection*/
    if(pipes==0)
    {
            execvp( argv[0], argv );
            execl(argv[0],argv[0],NULL);
            execl(argv[0],argv[0],argv[1],NULL);
	        execl( argv[0], argv[0],argv[1],argv[2],NULL);
            printf ( " didn't exec \n ");
    }
    else
    {
        for(int i=0;i<=pipes;i++,processes--,pipespp--)
        {

        if(pipespp>0 && processes>1)
        {/*create the right pipe if these two conditions are true*/
            pipe(r_fd);
        }

        pid=fork();

        if(pid<0)
        {
            printf("ERROR");
        }
        else if(pid>0)/*the parent part that she wrote the program for us*/
        {
            if(i>0)
            {
                close(l_fd[0]);
                close(l_fd[1]);
            }
            l_fd[0]=r_fd[0];
            l_fd[1]=r_fd[1];
        }
        else
        {
            if(inputflag==2 && processes==y)
            {/*handle input redir*/
                w=open("input.txt",O_RDONLY);
                close(0);
                dup(w);
                close(w);
                execl(input,input,NULL);
            }
            if(pipespp>0)
            {/* 1.1st process*/
                if(processes==y)
                {
                   close(1);
                   dup(r_fd[1]);
                   close(r_fd[0]);
                   close(r_fd[1]);
                   execl(argv[startposition[i]],argv[startposition[i]],NULL);
                }

             /*2. last process*/
                else if(processes==1)
                {
                    close(0);
                    dup(l_fd[0]);
                    close(l_fd[0]);
                    close(l_fd[1]);
                    execl(argv[startposition[i]],argv[startposition[i]],NULL);
                }
             /*3.middle process*/
                else
                {
                   close(0);
                   dup(l_fd[0]);
                   close(1);
                   dup(r_fd[1]);
                   close(l_fd[0]);
                   close(l_fd[1]);
                   close(r_fd[0]);
                   close(r_fd[1]);
                   execl(argv[startposition[i]],argv[startposition[i]],NULL);
                }
            }
         if(outputflag==3 && processes==1)
         {/*handle output redir*/
           w=creat("output.txt",0755);
           close(1);
           dup(w);
           close(w);

           execl(output,output,NULL);
         }

        }
    }
    }


    wait(&status);
    }

    return 0;
}
