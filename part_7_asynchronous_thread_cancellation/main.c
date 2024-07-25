#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
// Now assume that we have two threads. thread_1 and thread_2. They both are in operation and thread_1 tries to cancel thread_2. The thread_1 sends a cancellation request [CR(pthread_cancel)].

// When a thread tries to cancel another threat, the cancellation request [CR(pthread_cancel())] is queued by OS. It isn't delivered immediately.

// The OS afterwards, looks for an opportunity to terminate thread T2.

// OS may not terminate the thread instantly (Asynchronous).

pthread_t thread1, thread2;

void* task(void* arg) {
    printf("Thread 1: Starting task\n");
    for (int i = 0; i < 10; i++) {
        printf("Thread 1: Working on iteration %d\n", i + 1);
        sleep(1); // Simulate some work with sleep
    }
    printf("Thread 1: Task completed\n");
    return NULL;
}

void* cancel_task(void* arg) {
    sleep(3); // Let Thread 1 run for a bit before cancelling
    printf("Thread 2: Cancelling Thread 1\n");
    pthread_cancel(thread1);
    return NULL;
}

int main() {
    int result;

    // Create Thread 1
    result = pthread_create(&thread1, NULL, task, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    // Create Thread 2
    result = pthread_create(&thread2, NULL, cancel_task, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main thread: Both threads have finished\n");
    return 0;
}



