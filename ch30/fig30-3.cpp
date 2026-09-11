#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

int done = 0;
std::mutex m;
std::condition_variable c;

void thr_exit() {
    std::unique_lock<std::mutex> lock(m);
    // I don't know how to get this to work
    // without unique_lock, I ended up using ai
    // we're lowkey cooked ngl
    done = 1;
    c.notify_one();
}

void child() {
    std::cout << "child\n";
    thr_exit();
}

void thr_join() {
    std::unique_lock<std::mutex> lock(m);
    while (done == 0)
        c.wait(lock);
}


int main(void) {
    std::cout << "parent: begin\n";
    std::thread p(child);
    thr_join();
    p.join();
    std::cout << "parent: end\n";
    
    return 0;
}
