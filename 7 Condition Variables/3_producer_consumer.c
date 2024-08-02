#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;

void *producer(void *param) {
    while (1) {
        int item = rand() % 100;
        pthread_mutex_lock(&mutex);
        printf("---->Producer got the lock\n");
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_producer, &mutex);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Produced: %d\n", item);

        pthread_cond_signal(&cond_consumer);

        pthread_mutex_unlock(&mutex);
        printf("---->Producer left the lock\n");
        sleep(1);
    }
    return NULL;
}

void *consumer(void *param) {
    while (1) {

        pthread_mutex_lock(&mutex);
        printf("->Consumer got the lock\n");
        while (count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumed: %d\n", item);

        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
        printf("->Consumer left the lock\n");
        sleep(1);
    }
    return NULL;
}
int main() {
    pthread_t tid_producer, tid_consumer;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);

    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);
    return 0;
}
