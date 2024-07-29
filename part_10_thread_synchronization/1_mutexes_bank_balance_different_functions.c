#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep

#define NUM_OPERATIONS 10

int bank_balance = 1000;
pthread_mutex_t mutex;

void* increase_balance(void* arg) {
    int thread_id = *((int*)arg);
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        int amount = rand() % 100;
        bank_balance += amount;
        printf("---> This is thread %d increasing balance\nIncreases by %d amount, the new balance is %d\n", thread_id, amount, bank_balance);

        sleep(1); // Sleep for 1 second inside the critical section to simulate long operation

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

        sleep(1); // Sleep for 1 second inside the critical section to simulate long operation

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[2];
    int thread_ids[2] = {1, 2};

    pthread_create(&threads[0], NULL, increase_balance, (void*)&thread_ids[0]);
    pthread_create(&threads[1], NULL, decrease_balance, (void*)&thread_ids[1]);

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

