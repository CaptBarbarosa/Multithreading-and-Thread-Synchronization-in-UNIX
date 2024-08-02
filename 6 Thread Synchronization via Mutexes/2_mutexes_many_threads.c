#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For usleep

#define NUM_OPERATIONS 10
#define NUM_THREADS 10

int bank_balance = 1000;
pthread_mutex_t mutex;

void* increase_balance(void* arg) {
    int thread_id = *((int*)arg);
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        int amount = rand() % 100;
        bank_balance += amount;
        printf("---> This is thread %d increasing balance\nIncreases by %d amount, the new balance is %d\n", thread_id, amount, bank_balance);
        usleep(200000); // Sleep for 200 milliseconds
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* decrease_balance(void* arg) {
    int thread_id = *((int*)arg);
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        int amount = rand() % 100; // Random amount between 0 and 99
        bank_balance -= amount;
        printf("-> This is thread %d decreasing balance\nDecreases by %d amount, the new balance is %d\n", thread_id, amount, bank_balance);
        usleep(200000); // Sleep for 200 milliseconds
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (thread_ids[i] % 2 == 0) {
            pthread_create(&threads[i], NULL, increase_balance, (void*)&thread_ids[i]);
        } else {
            pthread_create(&threads[i], NULL, decrease_balance, (void*)&thread_ids[i]);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
   return 0;
}

