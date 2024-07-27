#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* child_thread_function(void* arg) {
    int i = 0;
    while(i < 5) { // Child performs some tasks
        printf("Child thread is running i=%d\n", i);
        sleep(1);
        i++;
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t child_thread;
    pthread_attr_t attr;
    if (pthread_attr_init(&attr)!=0){ //Initialized the attribute
        printf("Failed to initialize attribute");
    }
    if(pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE)!=0){ // Made it joinable
        printf("Failed to set it joinable");
    }
    if (pthread_create(&child_thread, &attr, child_thread_function, NULL) != 0){ //Threads are joinable by default actually.
        printf("Failed to create thread\n");
        return 1;}

    printf("Parent thread is doing its thing\n"); // Perform some tasks
    if (pthread_join(child_thread, NULL) != 0) { // Wait for child to terminate and join.
        printf("Failed to join threads\n");
        return 1;
    }
    printf("Child thread has terminated and resources are released\n");
    return 0;
}

