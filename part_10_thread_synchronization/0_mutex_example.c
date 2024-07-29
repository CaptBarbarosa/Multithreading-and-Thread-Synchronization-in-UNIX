#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For usleep

#define NUM_OPERATIONS 10

int bank_balance = 1000;
pthread_mutex_t mutex;

void* modify_balance(void* arg) {
    int thread_id = *((int*)arg);
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        int amount = (rand() % 200) - 100; // Random amount between -100 and +100
        bank_balance += amount;
        if(thread_id==1){
            printf("---");}
        printf("->This is thread %d modifying\nModifies %d amount, the new balance is %d\n\n", thread_id, amount, bank_balance);
        sleep(2); //Please notice that till the thread wakes up and leaces the lock, other thread can't enter.
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[2];
    int thread_ids[2] = {1, 2};

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, modify_balance, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

