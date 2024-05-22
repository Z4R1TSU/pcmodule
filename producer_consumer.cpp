#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

const int QUEUE_THRESHOLD = 10;

std::mutex mtx;
std::condition_variable cv;

class Queue {
public:
    // push by producer
    void put(int val) {
        std::unique_lock<std::mutex> lock(mtx);
        // if queue if full, wait for consumer to pop
        // while (q.size() >= QUEUE_THRESHOLD) {
        //     cv.wait(lock);
        // }
        cv.wait(lock, [&]() -> bool { return q.size() < QUEUE_THRESHOLD; });
        q.push(val);
        cv.notify_all();
        std::cout << "Producer: " << val << std::endl;
    }

    // pop by consumer
    int get() {
        std::unique_lock<std::mutex> lock(mtx);
        // while (q.empty()) {
        //     cv.wait(lock);
        // }
        cv.wait(lock, [&]() -> bool { return !q.empty(); });
        int val = q.front();
        q.pop();
        std::cout << "Consumer: " << val << std::endl;
        cv.notify_all();
        return val;
    }

private:
    std::queue<int> q;
};

void producer(Queue *q) {
    for (int i = 0; i < 100; i ++) {
        q->Queue::put(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void consumer(Queue *q) {
    for (int i = 0; i < 100; i ++) {
        q->Queue::get();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    Queue q;

    std::thread t1(producer, &q);
    std::thread t2(consumer, &q);

    t1.join();
    t2.join();
}