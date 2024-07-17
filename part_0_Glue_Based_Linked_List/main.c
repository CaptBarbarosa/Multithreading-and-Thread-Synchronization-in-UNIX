#include "glthread.c"
#include <stdlib.h>
#include <stdio.h>

// Define an application-specific structure
typedef struct person_ {
    char name[30];
    int age;
    glthread_node_t glnode; // Glue thread node
} person_t;

int main() {
    // Create and initialize the glthread list
    glthread_t list;
    init_glthread(&list, offsetof(person_t, glnode));

    // Create and initialize some person structures
    person_t person1 = {.name = "Alice", .age = 25};
    person_t person2 = {.name = "Bob", .age = 30};
    person_t person3 = {.name = "Charlie", .age = 35};

    // Initialize the glthread nodes within the person structures
    glthread_node_init(&person1.glnode);
    glthread_node_init(&person2.glnode);
    glthread_node_init(&person3.glnode);

    // Add the person structures to the glthread list
    glthread_add(&list, &person1.glnode);
    glthread_add(&list, &person2.glnode);
    glthread_add(&list, &person3.glnode);

    // Iterate over the list and print the persons
    person_t *person_ptr;
    ITERATE_GL_THREADS_BEGIN(&list, person_t, person_ptr) {
        printf("Name: %s, Age: %d\n", person_ptr->name, person_ptr->age);
    } ITERATE_GL_THREADS_ENDS;

    // Remove a person from the list
    glthread_remove(&list, &person2.glnode);

    // Iterate over the list again and print the remaining persons
    printf("\nAfter removal:\n");
    ITERATE_GL_THREADS_BEGIN(&list, person_t, person_ptr) {
        printf("Name: %s, Age: %d\n", person_ptr->name, person_ptr->age);
    } ITERATE_GL_THREADS_ENDS;

    return 0;
}

