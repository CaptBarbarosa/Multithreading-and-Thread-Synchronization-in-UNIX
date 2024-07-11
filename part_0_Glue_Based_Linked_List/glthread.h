#ifndef __GLTHREADS__
#define __GLTHREADS_

typedef struct glthread_node_ {
    // Please recognize that there is no data value unlike traditional doubly linked lists.
    struct glthread_node_ *left;
    struct glthread_node_ *right;
}glthread_node_t;

typedef struct gldll_ {
    glthread_node_t *head;
    int (*key_match)(void *, void *); 
    /* Func. pointer to a key_match function. Takes 2 void arguments and returns an 'int'. Please note that the void pointers allow for flexibility in the type of data stored in the list nodes.*/
    int (*comparison_fn)(void *, void *); 
    unsigned int offset;
}gldll_t;

/* 
   In the traditional doubly linked lists we'd have a void *data. Te void pointer is for efficiency and as you can observe we don't have a void pointer in the gll. But then, how is the glued data structure holds the data?
   The traditional d.l.l


*/

#endif
