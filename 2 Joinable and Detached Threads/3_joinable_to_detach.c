#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_function(void* arg) {
    printf("Thread started\n");
    sleep(2); // Simulate some work
    printf("Thread finished\n");
    return NULL;
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) { // Created a joinable thread (It is joinable by default)
        printf("Couldn't create thread\n");
        return 1;
    }

    if (pthread_detach(thread) != 0) { // Detached the thread
        printf("Error detaching thread\n");
        return 1;
    }

    printf("Thread detached\n");
    sleep(3);
    if (pthread_join(thread, NULL) != 0) {
        printf("Failed to join thread\n");
    }

    return 0;
}

