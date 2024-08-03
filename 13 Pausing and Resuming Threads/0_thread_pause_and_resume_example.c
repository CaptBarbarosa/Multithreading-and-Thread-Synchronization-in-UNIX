#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t pause_mutex;
pthread_cond_t pause_cond;
int pause_flag = 0;
void thread_pause() {
    pthread_mutex_lock(&pause_mutex);
    pause_flag = 1;
    pthread_mutex_unlock(&pause_mutex);
}
void thread_resume() {
    pthread_mutex_lock(&pause_mutex);
    pause_flag = 0;
    pthread_cond_signal(&pause_cond);
    pthread_mutex_unlock(&pause_mutex);
}
void thread_test_and_pause() {
    pthread_mutex_lock(&pause_mutex);
    while (pause_flag) {
        pthread_cond_wait(&pause_cond, &pause_mutex);
    }
    pthread_mutex_unlock(&pause_mutex);
}
void thread_set_pause(int pause) {
    pthread_mutex_lock(&pause_mutex);
    pause_flag = pause;
    if (!pause) {
        pthread_cond_signal(&pause_cond);
    }
    pthread_mutex_unlock(&pause_mutex);
}
void* thread_func(void* arg) {
    while (1) {
        thread_test_and_pause();
        printf("Thread is running...\n");
        sleep(1);
    }
    return NULL;
}
int main() {
    pthread_t thread;
    pthread_mutex_init(&pause_mutex, NULL);
    pthread_cond_init(&pause_cond, NULL);
    pthread_create(&thread, NULL, thread_func, NULL);
    sleep(3); 
    printf("Pausing thread...\n");
    thread_pause(); 
    sleep(3); 
    printf("Resuming thread...\n");
    thread_resume(); 
    sleep(3); 
    printf("Setting pause state to 1...\n");
    thread_set_pause(1); 
    sleep(3); 
    printf("Setting pause state to 0...\n");
    thread_set_pause(0); 
    sleep(3); 
    pthread_cancel(thread); 
    pthread_join(thread, NULL);
    pthread_mutex_destroy(&pause_mutex);
    pthread_cond_destroy(&pause_cond);
    return 0;
}

