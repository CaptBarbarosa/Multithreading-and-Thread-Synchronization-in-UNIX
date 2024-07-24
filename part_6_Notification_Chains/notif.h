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
GLTHREAD_TO_STRUCT(glthread_glue_to_notif_chain_elem, notif_chain_elem_t, glue);

typedef struct notif_chain_ {
    char nfc_name[64];
    glthread_t notif_chain_head;
} notif_chain_t;

#endif /* __NOTIF_CHAIN__ */

