#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *threadB(void * arg)
{
    for(int i=1;i<=10;i++)
    {
    printf("%d: BBBBBBBBB\n",i);
    printf("%d: BBBBBBBBB\n",i);
    printf("%d: BBBBBBBBB\n",i);
    printf("%d: BBBBBBBBB\n",i);
    printf("%d: BBBBBBBBB\n",i);
    printf("\n");
    }


    return NULL;
}
void threadA()
{
    for(int i=1;i<=10;i++)
    {
    printf("%d: AAAAAAAAA\n",i);
    printf("%d: AAAAAAAAA\n",i);
    printf("%d: AAAAAAAAA\n",i);
    printf("%d: AAAAAAAAA\n",i);
    printf("%d: AAAAAAAAA\n",i);
    printf("\n");
    }

}

int main()
{
    pthread_t thread;

    pthread_setconcurrency(2);

    pthread_create(&thread, NULL, threadB, NULL);



    threadA();

    pthread_join(thread, NULL);

    pthread_exit(0);
    return 0;
}
