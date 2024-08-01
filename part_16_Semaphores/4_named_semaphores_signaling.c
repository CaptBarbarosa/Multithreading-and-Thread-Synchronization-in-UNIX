#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define SEMAPHORE_NAME "/example_semaphore"

int main() {
    sem_t *sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    printf("Process 2: Sleeping for 2 seconds before signaling the semaphore...\n");
    sleep(2); // Simulate some work being done

    printf("Process 2: Signaling the semaphore...\n");
    if (sem_post(sem) < 0) {
        perror("sem_post");
        sem_close(sem);
        exit(EXIT_FAILURE);
    }

    printf("Process 2: Semaphore signaled!\n");

    sem_close(sem);

    return 0;
}

