#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_ITERATIONS 10
sem_t semaphore;
int shared_resource = 0;
void* thread_function(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sem_wait(&semaphore);
        int temp = shared_resource;
        printf("Thread %ld: Shared resource value: %d\n", (long)arg, temp);
        shared_resource = temp + 1;
        sleep(1);
        sem_post(&semaphore);
        sleep(1);
    }
    return NULL;
}
int main() {
    pthread_t thread1, thread2;
    sem_init(&semaphore, 0, 1);
    pthread_create(&thread1, NULL, thread_function, (void*)1);
    pthread_create(&thread2, NULL, thread_function, (void*)2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore);
    printf("Final value of shared resource: %d\n", shared_resource);
    return 0;
}

