#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void* thread_func(void* arg) {
    printf("Thread is running\n");
    return NULL;
}
int main() {
    pthread_t my_thread; // Defining thread
    pthread_attr_t attr; // Defining attribute
    pthread_attr_init(&attr); // Initializing attribute
    if (pthread_create(&my_thread, &attr, thread_func, NULL) != 0){ //Thread creation
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    pthread_attr_destroy(&attr); //Destroying attribute
    if (pthread_join(my_thread, NULL) != 0){ // Joining threads
        fprintf(stderr, "Error joining thread\n");
        return 1;
    }
    printf("Thread has terminated\n");
    return 0;
}

