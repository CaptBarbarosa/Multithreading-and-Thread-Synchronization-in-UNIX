#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define LOG_FILE "log.txt"
#define NUM_THREADS 5

// Declare the read-write lock
pthread_rwlock_t rwlock;

void* write_log(void* arg) {
    int id = *((int*)arg);
    pthread_rwlock_wrlock(&rwlock);
    printf("----- Writer Thread %d got the lock\n", id);

    FILE* file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        perror("Failed to open log file");
        pthread_rwlock_unlock(&rwlock);
        printf("Writer Thread %d released the lock\n", id);
        return NULL;
    }
    fprintf(file, "Log entry from writer %d\n", id);
    fclose(file);
    pthread_rwlock_unlock(&rwlock);
    printf("<<<<< Writer Thread %d released the lock\n", id);
    printf("------------------------------------------\n\n");

    return NULL;
}

void* read_log(void* arg) {
    int id = *((int*)arg);
    pthread_rwlock_rdlock(&rwlock);
    printf(">>>>>Reader Thread %d got the lock\n", id);
    FILE* file = fopen(LOG_FILE, "r");
    if (file == NULL) {
        perror("Failed to open log file");
        pthread_rwlock_unlock(&rwlock);
        printf("Reader Thread %d released the lock\n", id);
        return NULL;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Reader Thread %d: %s", id, buffer);
    }
    fclose(file);
    pthread_rwlock_unlock(&rwlock);
    printf("Reader Thread %d released the lock\n", id);
    printf("------------------------------------\n\n");

    return NULL;
}

int main() {
    // Initialize the read-write lock
    pthread_rwlock_init(&rwlock, NULL);

    // Create writer threads
    pthread_t writers[NUM_THREADS];
    int writer_ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, write_log, &writer_ids[i]);
    }

    // Create reader threads
    pthread_t readers[NUM_THREADS];
    int reader_ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, read_log, &reader_ids[i]);
    }

    // Wait for writer threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Wait for reader threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Destroy the read-write lock
    pthread_rwlock_destroy(&rwlock);

    return 0;
}

