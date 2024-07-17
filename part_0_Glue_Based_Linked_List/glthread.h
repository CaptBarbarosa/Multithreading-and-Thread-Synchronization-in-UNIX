#ifndef __GLTHREADS__
#define __GLTHREADS__

#include <stddef.h> // Include for size_t

// Define the glthread_node_ structure to be used as a node in the glthread list
typedef struct glthread_node_ {
    struct glthread_node_ *left;  // Pointer to the previous node in the list
    struct glthread_node_ *right; // Pointer to the next node in the list
} glthread_node_t;

// Define the glthread_ structure to represent the glthread list
typedef struct glthread_ {
    glthread_node_t *head;  // Pointer to the head node of the list
    size_t offset;    // Offset of the glthread node in the application-defined data structure
} glthread_t;

// Function to add a new node to the glthread list
void glthread_add(glthread_t *lst, glthread_node_t *glnode);

// Function to remove a node from the glthread list
void glthread_remove(glthread_t *lst, glthread_node_t *glnode);

// Macro to iterate over all nodes in a glthread list
#define ITERATE_GL_THREADS_BEGIN(lstptr, struct_type, ptr)      \
{                                                               \
    glthread_node_t *_glnode = NULL, *_next = NULL;             \
    for(_glnode = (lstptr)->head; _glnode; _glnode = _next){    \
        _next = _glnode->right;                                 \
        ptr = (struct_type *)((char *)_glnode - (lstptr)->offset);

#define ITERATE_GL_THREADS_ENDS }}

// Macro to initialize a glthread node
#define glthread_node_init(glnode)  \
    (glnode)->left = NULL;          \
    (glnode)->right = NULL;

// Function to initialize a glthread list
void init_glthread(glthread_t *glthread, size_t offset);

#endif /* __GLTHREADS__ */

