#include <pthread.h>
#include <stdio.h>
void* thread_function(void* arg) {
    printf("Detached thread is running\n");
}
int main() {
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr); //Initing the attribute
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //We set the thread to be detached
    pthread_create(&thread, &attr, thread_function, NULL); //Creating the thread
    printf("Detached thread has been created\n");
    if (pthread_join(thread, NULL) != 0) { //Wait for child to terminate and join it.
        fprintf(stderr, "Error joining thread\n");
        return 1;}
    return 0;
}

