#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

pthread_mutex_t mutexFuel;
int fuel = 50;

void* routine(void* args){
    if(pthread_mutex_lock(&mutexFuel)==0){
        printf("->Thread %d acquired the lock\n",(*(int *)args));}
    if(pthread_mutex_lock(&mutexFuel)==0){
        printf("-->Thread %d acquired the lock\n",(*(int *)args));}
    if(pthread_mutex_lock(&mutexFuel)==0){
        printf("--->Thread %d acquired the lock\n",(*(int *)args));}
    if(pthread_mutex_lock(&mutexFuel)==0){
        printf("---->Thread %d acquired the lock\n",(*(int *)args));}
    if(pthread_mutex_lock(&mutexFuel)==0){
        printf("----->Thread %d acquired the lock\n",(*(int *)args));}
    fuel += 50;
    printf("Thread %d incremented fuel to %d\n", (*(int*)args), fuel);
    if(pthread_mutex_unlock(&mutexFuel)==0){
        printf("----->Thread %d released the lock\n",(*(int *)args));}
    if(pthread_mutex_unlock(&mutexFuel)==0){
        printf("---->Thread %d released the lock\n",(*(int *)args));}
    if(pthread_mutex_unlock(&mutexFuel)==0){
        printf("--->Thread %d released the lock\n",(*(int *)args));}
    if(pthread_mutex_unlock(&mutexFuel)==0){
        printf("-->Thread %d released the lock\n",(*(int *)args));}
    if(pthread_mutex_unlock(&mutexFuel)==0){
        printf("->Thread %d released the lock\n",(*(int *)args));}
        printf("----------------------------------\n\n");
    free(args);
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    pthread_mutexattr_t recursiveMutexAttributes;
    pthread_mutexattr_init(&recursiveMutexAttributes);
    pthread_mutexattr_settype(&recursiveMutexAttributes, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutexFuel, &recursiveMutexAttributes);
    int i;
    for (i = 0; i < THREAD_NUM; i++){
        int *a=malloc(sizeof(int));
        *a=i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    printf("Fuel: %d\n", fuel);
    pthread_mutexattr_destroy(&recursiveMutexAttributes);
    pthread_mutex_destroy(&mutexFuel);
    return 0;
}
