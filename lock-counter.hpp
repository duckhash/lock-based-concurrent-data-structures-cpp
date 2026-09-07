#pragma once

#include <mutex>

typedef struct __counter_t {
    int value = 0;
    std::mutex lock;
} counter_t;

void init (counter_t *c) { //unecessary, kept for resetting idk
    c->value = 0;
}

void increment(counter_t *c) {
    c->lock.lock();
    c->value++;
    c->lock.unlock();
}

void decrement(counter_t *c) {
    c->lock.lock();
    c->value--;
    c->lock.unlock();
}

int get(counter_t *c) {
    c->lock.lock();
    int rc = c->value;
    c->lock.unlock();
    return rc;
}
