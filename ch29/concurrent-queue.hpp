#pragma once

#include <mutex>
#include <cassert>
#include <cstdlib>

// I like to use assert more for debugging
// and perror for actual error handling.
//
// Writing it down because I mixed them up (talk about amateur mistakes, sorry!)
struct node_t {
    int value;
    node_t *next;
};

struct queue_t {
    node_t *head;
    node_t *tail;
    std::mutex head_lock, tail_lock; // Double trouble haha!
};

void Queue_Init(queue_t *q) {
    node_t *tmp = (node_t *) malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
}

void Queue_Enqueue(queue_t *q, int value) {
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL); // Did you know assert doesn't do anything if it's a production build?
    tmp->value = value;
    tmp->next = NULL;

    q->tail_lock.lock();
    q->tail->next = tmp;
    q->tail = tmp;
    q->tail_lock.unlock();
}

int Queue_Dequeue(queue_t *q, int *value) {
    q->head_lock.lock();
    node_t *tmp = q->head;
    node_t *new_head = tmp->next;
    if (new_head == NULL) {
        q->head_lock.unlock();
        return -1;
    }

    *value = new_head->value;
    q->head = new_head;
    q->head_lock.unlock();
    free(tmp);
    return 0;
}
