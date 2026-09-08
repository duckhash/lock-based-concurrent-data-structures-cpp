// I remember, I was reading an older version of OSTEP
// where the approximate counter, was called "sloppy counter" haha!
// Or idk, maybe I'm just hallucinating (I swear I'm not AI!)
// Although I do think that "sloppy counter" is a much more fitting name.

#pragma once

#include <mutex>

#ifndef NUMCPUS
#define NUMCPUS 4 //hardcoded, yikes!
#endif

struct counter_t {
    int        global;
    std::mutex glock; // lol, from global + clock = glock
    int        local[NUMCPUS];
    std::mutex llock[NUMCPUS];
    int        threshold;
};

void init(counter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    int i;
    for (i = 0; i < NUMCPUS; ++i) {
        c->local[i] = 0;
    }
}

void update(counter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;
    c->llock[cpu].lock();
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {
        c->glock.lock();
        c->global += c->local[cpu];
        c->glock.unlock();
        c->local[cpu] = 0;
    }
    c->llock[cpu].unlock();
}

int get(counter_t *c) {
    c->glock.lock();
    int val = c->global;
    c->glock.unlock();
    return val;
}
