#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* child_thread_function(void* arg){
    int i=0;
    while(i<5){ //Child performs some tasks
        printf("Child thread is running i=%d\n",i);
        sleep(1);
        i++;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t child_thread;

    if (pthread_create(&child_thread, NULL, child_thread_function, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;}

    printf("Parent thread is doing its thing\n");// Perform some task
    if (pthread_join(child_thread, NULL) != 0) { //Wait for child to terminate and join it.
        fprintf(stderr, "Error joining thread\n");
        return 1;}
    printf("Child thread has terminated and resources are released\n");
    return 0;
}

