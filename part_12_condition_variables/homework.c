#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_QUEUE_SIZE 5
typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;
Queue queue;
pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}
void enqueue(Queue *q, int value) {
    if (q->size < MAX_QUEUE_SIZE) {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->data[q->rear] = value;
        q->size++;
    }
}
int dequeue(Queue *q) {
    int value = -1;
    if (q->size > 0) {
        value = q->data[q->front];
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        q->size--;
    }
    return value;
}
void *producer(void *param) {
    int id = *((int *)param);
    while (1) {
        int item = rand() % 100;
        pthread_mutex_lock(&mutex);
        while (queue.size == MAX_QUEUE_SIZE) {
            pthread_cond_wait(&cond_producer, &mutex);
        }
        enqueue(&queue, item);
        printf("Producer %d produced %d\n", id, item);
        if (queue.size == MAX_QUEUE_SIZE) {
            pthread_cond_signal(&cond_consumer);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(0);
}
void *consumer(void *param) {
    int id = *((int *)param);
    while (1) {
        pthread_mutex_lock(&mutex);
        while (queue.size == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        while (queue.size > 0) {
            int item = dequeue(&queue);
            printf("Consumer %d consumed %d\n", id, item);
        }
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(0);
}

int main() {
    pthread_t producers[2], consumers[2];
    int producer_ids[2] = {1, 2};
    int consumer_ids[2] = {1, 2};

    initQueue(&queue);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}

