#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

sem_t semaphore;

void *bathroom(void *args){
    int semaphore_value;
    printf("->Thread[%d] has arrived\n",* ((int *)args));
    sem_wait(&semaphore);
    sem_getvalue(&semaphore, &semaphore_value);
    printf("Thread[%d] got the semaphore and the semvalue is: %d\n",(*(int*)args),semaphore_value);
    sleep(1);
    sem_post(&semaphore);
    printf("Thread[%d] has finished its job\n",*((int *)args));
    free(args);
}

int main(){
    sem_init(&semaphore, 0, 2);
    pthread_t thread_array[10];
    int i;
    for(i=0;i<10;i++){
        int *a = malloc(sizeof(int));
        if(a==NULL){
            printf("Failed to create a\n");
            exit(1);
        }
        *a = i;
        if(pthread_create(&thread_array[i], NULL, &bathroom, a) != 0){
            printf("Failed to create thread_array[%d]\n");
            exit(1);
        }
    }

    for(i=0; i<10; i++){
        pthread_join(thread_array[i], NULL);
    }
    sem_destroy(&semaphore);
    return 0;
}

