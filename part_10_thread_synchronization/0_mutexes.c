#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int id = 0;

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
    cust_to_add->bank_balance = 1000 + rand() % 10000; // Random bank balance between 1000 and 10999
    cust_to_add->next = NULL;
    if (tail != NULL) {
        tail->next = cust_to_add;
    }
    return cust_to_add;
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
    Customer *head = (Customer *)malloc(sizeof(Customer));
    Customer *tail = head;
    head->next = NULL;
    while (id < 10) {
        tail = create_Customer(tail);
    }
    write_ids_to_file(head);
    return 0;
}

