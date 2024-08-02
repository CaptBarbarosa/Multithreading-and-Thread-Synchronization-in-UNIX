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

    printf("Process 1: Waiting for the semaphore...\n");
    if (sem_wait(sem) < 0) {
        perror("sem_wait");
        sem_close(sem);
        exit(EXIT_FAILURE);
    }

    printf("Process 1: Semaphore acquired!\n");

    sem_close(sem);
    sem_unlink(SEMAPHORE_NAME);

    return 0;
}

