#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t barrier;

void* routine(void* args) {
    int id = *((int *)args);
    printf("Waiting at the barrier I am thread %d...\n", id);
    pthread_barrier_wait(&barrier); //Each thread can come up to this point but waits here until the enough number of threads arrive here.
    printf("The barrier is passed thread %d\n",id);
}

int main(int argc, char *argv[]) {
    pthread_t th[10];
    int i;
    pthread_barrier_init(&barrier, NULL, 10); //Step 1: Initialized barrier and specified the number.
    for (i = 0; i < 10; i++) {
        if (pthread_create(&th[i], NULL, &routine, &i) != 0){//Step 2: Create thread and send it to the function
            printf("Failed to create thread");
        }
        usleep(50000);
    }
    for (i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Failed to join thread");
        }
    }
    pthread_barrier_destroy(&barrier);
    return 0;
}
