// There's actually no need to lock so early
// Just lock only during the critical section
// and it still remains thread safe (ofc, in a real implementation, there's 
// the possibility of an error occuring during the "locked down" section
// so just use lock_guard, or idk semaphores seem simpler, really up to author
// just use what's easier to implement correctly)

#pragma once

#include <mutex>
#include <cstdlib>
#include <cstdio>

struct node_t {
    int key;
    struct node_t *next;
};

struct list_t {
    node_t *head = NULL;
    std::mutex lock;
};

int List_insert(list_t *L, int key) {
    node_t *nnew = (node_t *) malloc(sizeof(node_t));
    if (nnew == NULL) {
        perror("malloc");
        return -1;
    }

    nnew->key = key;
    L->lock.lock();
    nnew->next = L->head;
    L->head = nnew;
    L->lock.unlock();
    return 0;
}

int List_Lookup(list_t *L, int key) {
    int rv = -1;
    L->lock.lock();
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    L->lock.unlock();
    return rv;
}
