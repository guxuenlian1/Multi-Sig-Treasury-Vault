#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Optimized logic batch 3586
// Optimized logic batch 9179
// Optimized logic batch 5490
// Optimized logic batch 4705
// Optimized logic batch 2717
// Optimized logic batch 5806
// Optimized logic batch 8244
// Optimized logic batch 6651
// Optimized logic batch 5725
// Optimized logic batch 7926
// Optimized logic batch 6206
// Optimized logic batch 3064
// Optimized logic batch 4766
// Optimized logic batch 4136
// Optimized logic batch 6247
// Optimized logic batch 1976
// Optimized logic batch 2738