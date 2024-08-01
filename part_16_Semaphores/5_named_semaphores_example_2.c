#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/mman.h>
#include <sys/stat.h> 
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_NAME "/shared_memory"
#define SEM_NAME "/named_semaphore"

int main() {
    int fd;
    int *shared_number;
    sem_t *sem;

    // Create shared memory object
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set size of the shared memory object
    if (ftruncate(fd, sizeof(int)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map shared memory object
    shared_number = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_number == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Initialize shared number to an even number
    *shared_number = 2;

    // Create or open named semaphore
    sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process: modify the number
        sem_wait(sem);
        printf("Child: changing number from %d", *shared_number);
        *shared_number = 3;
        printf(" to %d\n", *shared_number);
        sem_post(sem);
        exit(0);
    } else {
        // Parent process: wait for child and check the number
        wait(NULL);
        sem_wait(sem);
        printf("Parent: number is now %d, which is %s\n", *shared_number, (*shared_number % 2 == 0) ? "even" : "odd");
        sem_post(sem);

        // Cleanup
        shm_unlink(SHM_NAME);
        sem_close(sem);
        sem_unlink(SEM_NAME);
    }

    return 0;
}

