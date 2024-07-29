#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_CUSTOMERS 10
#define NUM_THREADS 2
#define NUM_OPERATIONS 1000

int id = 0;
pthread_mutex_t mutex;

typedef struct Customer {
    int customer_id;
    int bank_balance;
    struct Customer *next;
} Customer;

Customer* create_Customer(Customer *tail) {
    Customer *cust_to_add = (Customer *)malloc(sizeof(Customer));
    if (cust_to_add == NULL) {
        printf("Failed to create customer struct in create_Customer\n");
        exit(1);
    }
    cust_to_add->customer_id = id++;
    cust_to_add->bank_balance = 1000 + rand() % 10000; 
    cust_to_add->next = NULL;
    if (tail != NULL) {
        tail->next = cust_to_add;
    }
    return cust_to_add;
}

void* modify_balance(void* arg) {
    Customer* head = (Customer*) arg;
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        Customer* current = head->next;
        while (current != NULL) {
            if (rand() % 2) {
                current->bank_balance += rand() % 100;
            } else {
                current->bank_balance -= rand() % 100;
            }
            current = current->next;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void write_ids_to_file(Customer *head) {
    FILE *file = fopen("customers.txt", "w");
    if (file == NULL) {
        printf("Failed to open file for writing\n");
        exit(1);
    }

    Customer *current = head->next;
    while (current != NULL) {
        fprintf(file, "Customer ID: %d, Bank Balance: %d\n", current->customer_id, current->bank_balance);
        current = current->next;
    }

    fclose(file);
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    Customer *head = (Customer *)malloc(sizeof(Customer));
    Customer *tail = head;
    head->next = NULL;
    while (id < NUM_CUSTOMERS) {
        tail = create_Customer(tail);
    }

    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, modify_balance, (void*)head);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    write_ids_to_file(head);

    pthread_mutex_destroy(&mutex);
    return 0;
}

