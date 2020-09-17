#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *threadB(void * arg)
{
    /*Sleep(1);*/



    for(int i=1;i<=10;i++)
    {
  pthread_mutex_lock(&mutex);
    printf("%d: BBBBBBBBB\n",i);
    printf("%d: BBBBBBBBB\n",i);
    printf("%d: BBBBBBBBB\n",i);
    printf("%d: BBBBBBBBB\n",i);
    printf("%d: BBBBBBBBB\n",i);
    printf("\n");
  pthread_mutex_unlock(&mutex);
    }


    return NULL;
}
void threadA()
{
    /*Sleep(1);*/

    for(int i=1;i<=10;i++)
    {
pthread_mutex_lock(&mutex);
    printf("%d: AAAAAAAAA\n",i);
    printf("%d: AAAAAAAAA\n",i);
    printf("%d: AAAAAAAAA\n",i);
    printf("%d: AAAAAAAAA\n",i);
    printf("%d: AAAAAAAAA\n",i);
    printf("\n");
pthread_mutex_unlock(&mutex);
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
