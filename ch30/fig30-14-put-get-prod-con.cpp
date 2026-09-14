const int MAX = 10;
int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put (int value) {
  buffer[fill_ptr] = value;
  fill_ptr = (fill_ptr + 1) % MAX;
  ++count;
}

int get() {
  int tmp = buffer[use_ptr];
  use_ptr = (use_ptr + 1) % MAX;
  --count;
  return tmp;
}

// Producer/Consumer Synchronization

#include <iostream>
#include <condition_variable>
#include <mutex>

int loops = 5; // OSTEP has a comment "must initialize somewhere"
std::mutex mutex;
std::condition_variable empty, fill;

void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    std::unique_lock<std::mutex> lock(mutex);
    while (count == MAX)
      empty.wait(lock);
    put(i);
    fill.notify_one();
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    std::unique_lock<std::mutex> lock(mutex);
    while(count == 0)
      fill.wait(lock);
    int tmp = get();
    empty.notify_one();
    cout << tmp << '\n';
  }
}
