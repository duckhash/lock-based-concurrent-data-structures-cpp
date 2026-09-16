#define MAX 5
int buffer[MAX];
int fill = 0;
int use = 0;

void put (int value) {
  buffer[fill] = value;
  fill = (fill + 1) % MAX;
}

int get() {
  int tmp = buffer[use_ptr];
  use = (use_ptr + 1) % MAX;
  return tmp;
}

// Producer/Consumer Synchronization

#include <iostream>
#include <semaphore>
#include <mutex>

int loops = 5; // OSTEP has a comment "must initialize somewhere"
std::counting_semaphore<10> empty(MAX), fill(0);
std::mutex mtx;

void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    empty.acquire();
    mtx.lock();
    put(i);
    mtx.unlock();
    fill.release();
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    full.acquire();
    mtx.lock();
    int tmp = get();
    mtx.unlock();
    empty.release();
    cout << tmp << '\n';
  }
}
