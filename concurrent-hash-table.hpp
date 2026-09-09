#pragma once

#include "./concurrent-linked-list-rewritten.hpp"

#define BUCKETS (101) // mmmmm, kfc bucket

struct hash_t {
    list_t lists[BUCKETS];
};

// btw if you use a negative number, your computer will blow up
// I'll keep the hash-table minimal, you get the point tho, right?

int Hash_Insert(hash_t *H, int key) {
    return List_Insert(&H->lists[key % BUCKETS], key);
}

int Hash_Lookup(hash_t *H, int key) {
    return List_Lookup(&H->lists[key % BUCKETS], key);
}
