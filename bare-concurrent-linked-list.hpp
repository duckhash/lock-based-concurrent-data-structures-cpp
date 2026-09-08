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
// But sir- why aren't you using class syntax? What's the point of translating here?

// Great question, python drove me insane and now every chance I get I avoid OOP and
// let the C insticts take over. 
//
// jk
// Nothing against OOP, I enjoy it, and prefer it,
// I just got a little bored!

int List_Insert(list_t *L, int key) {
    L->lock.lock();
    node_t *nnew = (node_t*) malloc(sizeof(node_t)); // "new" is a keyword in c++, ahem ahem, don't forget in C++, implicit conversion from *void is illegal!
    if (nnew == NULL) {
        perror("malloc");
        L->lock.unlock();
        return -1;
    }
    nnew->key = key;
    nnew->next = L->head;
    L->head = nnew;
    L->lock.unlock();
    return 0;
}

int List_Lookup(list_t *L, int key) {
    L->lock.lock();
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            L->lock.unlock();
            return 0;
        }
        curr = curr->next;
    }
    L->lock.unlock();
    return -1;
}
