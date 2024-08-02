#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_t thread1, thread2;
void* task(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // You can set whether or not a thread is cancellable via pthread_setcancelstate.
    // If you uncomment the code below, you will observe that the thread 2 will fail to cancel it.
    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,0);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); // Specified the cancellation type
    printf("Thread 1: Starting task\n");
    for (int i = 0; i < 5; i++){
        printf("Thread 1: Working on iteration %d\n", i + 1);
        sleep(1); // Simulate some work with sleep
    }
    printf("Thread 1: Task completed\n");
    return NULL;
}

void* cancel_task(void* arg) {
    sleep(3); // Let thread 1 run for a bit before cancelling
    printf("Thread 2: Cancelling Thread 1\n");
    pthread_cancel(thread1);
    return NULL;
}

int main() {
    if(pthread_create(&thread1, NULL, task, NULL)!=0){
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    if(pthread_create(&thread2, NULL, cancel_task, NULL)!=0){
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Main thread: Both threads have finished\n");
    return 0;
}
