#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For usleep

#define NUM_OPERATIONS 10

int bank_balance = 1000;
pthread_mutex_t mutex;

void* modify_balance(void* arg) {
    int thread_id = *((int*)arg);
    for (int i = 0; i < NUM_OPERATIONS; i++){
        //Please notice that till the thread wakes up and leaves the lock, other thread can't enter
        //Both threads arrive at almost the same time. And both sleep for one seconds. 
        //Lets say thread one gets the lock first. Thread 2 waits for the lock. It blocks till it gets lock.
        //Afterwards thread 1 ends and releases the lock. And thread 2 gets it while thread 1 sleeps for a second.
        sleep(1);
        pthread_mutex_lock(&mutex);

        int amount = (rand() % 200) - 100; // Random amount between -100 and +100
        bank_balance += amount;
        if(thread_id==1){
            printf("---");}
        printf("->This is thread %d modifying\nModifies %d amount, the new balance is %d\n\n", thread_id, amount, bank_balance);
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

