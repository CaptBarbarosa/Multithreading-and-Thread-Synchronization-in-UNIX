#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int condition_met = 0;
void* wait_thread(void* arg) {
    int thread_id = *((int*)arg);
    pthread_mutex_lock(&mutex);
    while (!condition_met) {
        printf("Thread %d waiting...\n", thread_id);
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Thread %d proceeding...\n", thread_id);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void* signal_thread(void* arg) {
    sleep(1); // Simulating some work before signaling
    pthread_mutex_lock(&mutex);
    condition_met = 1;
    printf("Thread 3 signaling all waiting threads...\n");
    pthread_cond_broadcast(&cond); // Releases based on the ¾cond 
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main() {
    pthread_t t1, t2, t3;
    int t1_id = 1, t2_id = 2;
    pthread_create(&t1, NULL, wait_thread, &t1_id);
    pthread_create(&t2, NULL, wait_thread, &t2_id);
    pthread_create(&t3, NULL, signal_thread, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
