#ifndef __NOTIF_CHAIN__
#define __NOTIF_CHAIN__

#include <stddef.h> /* for size_t */
#include "utils.h"
#include "glthread/glthread.h"

#define MAX_NOTIF_KEY_SIZE 64

typedef void (*nfc_app_cb)(void *, size_t);

typedef struct notif_chain_elem_ {
    char key[MAX_NOTIF_KEY_SIZE];
    size_t key_size;
    bool_t is_key_set;
    nfc_app_cb app_cb;
    glthread_t glue;
} notif_chain_elem_t;
#define GLTHREAD_TO_STRUCT(glthread_node, container_type, field_name)  \
    ((container_type *)((char *)(glthread_node) - offsetof(container_type, field_name)))


typedef struct notif_chain_ {
    char nfc_name[64];
    glthread_t notif_chain_head;
} notif_chain_t;


#endif /* __NOTIF_CHAIN__ */

