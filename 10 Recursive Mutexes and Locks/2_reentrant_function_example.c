#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex;

void inner_function(int thread_id) {
    pthread_mutex_lock(&mutex);
    printf("----Thread %d acquired the lock at inner function\n",thread_id);
    pthread_mutex_unlock(&mutex);
    printf("<<<Thread %d released the lock at inner function\n",thread_id);
}

void outer_function(int thread_id){
    pthread_mutex_lock(&mutex);
    printf("----- Thread %d acquired the lock at outer function\n",thread_id);
    inner_function(thread_id);
    printf("<<Thread %d will release the lock at outer function\n",thread_id);
    printf("----------------------------------------------------\n");
    pthread_mutex_unlock(&mutex); // Released after printing so that it would print in order
}

void* thread_routine(void* args) {
    outer_function((*(int *)args));
    free(args);
    return NULL;
}

int main() {
    pthread_t thread[5];
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);

    int i;
    for(i=0; i<5; i++){
        int *a=malloc(sizeof(int));
        *a=i;
        pthread_create(&thread[i], NULL, thread_routine, a);}
    for(i=0; i<5; i++){
        pthread_join(thread[i], NULL);}

    // Destroy the mutex and its attributes
    pthread_mutexattr_destroy(&attr);
    pthread_mutex_destroy(&mutex);

    return 0;
}

