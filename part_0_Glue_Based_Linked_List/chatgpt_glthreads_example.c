#include <stddef.h> // For offsetof
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Define the glthread node structure
typedef struct glthread_node_ {
    struct glthread_node_ *left;
    struct glthread_node_ *right;
} glthread_node_t;

// Define the gldll structure
typedef struct gldll_ {
    glthread_node_t *head;
    int (*key_match)(void *, void *);
    int (*comparison_fn)(void *, void *);
    unsigned int offset;
} gldll_t;

// Example data structure (Employee)
typedef struct employee_ {
    char name[32];
    int age;
    glthread_node_t glnode; // glthread node embedded within the structure
} employee_t;

// Function to initialize a glthread node
void glthread_node_init(glthread_node_t *glnode) {
    glnode->left = NULL;
    glnode->right = NULL;
}

// Function to add a glthread node to the list
void glthread_add(gldll_t *gldll, glthread_node_t *glnode) {
    glnode->right = gldll->head;
    if (gldll->head) {
        gldll->head->left = glnode;
    }
    gldll->head = glnode;
    glnode->left = NULL;
}

// Function to search for an element in the list
void* glthread_search(gldll_t *gldll, void *key) {
    glthread_node_t *glnode = gldll->head;
    while (glnode) {
        void *data = (char *)glnode - gldll->offset;
        if (gldll->key_match(data, key)) {
            return data;
        }
        glnode = glnode->right;
    }
    return NULL;
}

// Function to print the employee list
void print_employee_list(gldll_t *gldll) {
    glthread_node_t *glnode = gldll->head;
    while (glnode) {
        employee_t *emp = (employee_t *)((char *)glnode - gldll->offset);
        printf("Name: %s, Age: %d\n", emp->name, emp->age);
        glnode = glnode->right;
    }
    printf("NULL\n");
}

// Key match function to compare employee names
int key_match(void *data, void *key) {
    employee_t *emp = (employee_t *)data;
    return strcmp(emp->name, (char *)key) == 0;
}

// Comparison function to compare employee ages
int comparison_fn(void *data1, void *data2) {
    employee_t *emp1 = (employee_t *)data1;
    employee_t *emp2 = (employee_t *)data2;
    return emp1->age - emp2->age;
}

int main() {
    gldll_t gldll;
    gldll.head = NULL;
    gldll.key_match = key_match;
    gldll.comparison_fn = comparison_fn;
    gldll.offset = offsetof(employee_t, glnode);

    employee_t emp1;
    strcpy(emp1.name, "Alice");
    emp1.age = 30;
    glthread_node_init(&emp1.glnode);
    glthread_add(&gldll, &emp1.glnode);

    employee_t emp2;
    strcpy(emp2.name, "Bob");
    emp2.age = 25;
    glthread_node_init(&emp2.glnode);
    glthread_add(&gldll, &emp2.glnode);

    print_employee_list(&gldll);

    char *search_key = "Alice";
    employee_t *found = (employee_t *)glthread_search(&gldll, search_key);
    if (found) {
        printf("Found employee: %s, Age: %d\n", found->name, found->age);
    } else {
        printf("Employee not found\n");
    }

    return 0;
}

