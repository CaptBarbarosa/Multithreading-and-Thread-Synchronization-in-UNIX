#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
int condition = 0;
void* waiting_thread(void* arg) {
    pthread_mutex_lock(&mutex);
    while (condition == 0) {
        printf("Waiting for the condition to be met...\n");
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Condition met, continuing execution...\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void* signaling_thread(void* arg) {
    sleep(2);  
    pthread_mutex_lock(&mutex);
    condition = 1;
    printf("Condition met, signaling waiting thread...\n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&t1, NULL, waiting_thread, NULL);
    pthread_create(&t2, NULL, signaling_thread, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
