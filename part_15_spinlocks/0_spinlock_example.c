#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_spinlock_t spinlock;
int counter = 0;

void* thread_function(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_spin_lock(&spinlock);
        // Critical section
        counter++;
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the spinlock
    if (pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE) != 0) {
        perror("Failed to initialize spinlock");
        return 1;
    }

    // Create two threads
    if (pthread_create(&thread1, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }
    if (pthread_create(&thread2, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the spinlock
    pthread_spin_destroy(&spinlock);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}

