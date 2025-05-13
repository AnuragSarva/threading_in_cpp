
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <memory>
#include <chrono>

class Task {
public:
    void execute(int id) {
        std::cout << "Thread " << std::this_thread::get_id()
                  << " executing Task ID " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate work
    }
};

template <typename T>
class ObjectPool {
private:
    std::queue<std::shared_ptr<T>> pool;
    std::mutex mtx;
    std::condition_variable cv;
    int next_id = 0;

public:
    ObjectPool(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            pool.push(std::make_shared<T>());
        }
    }

    // Checkout object from pool
    std::shared_ptr<T> acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !pool.empty(); });

        auto obj = pool.front();
        pool.pop();
        return obj;
    }

    // Return object back to pool
    void release(std::shared_ptr<T> obj) {
        std::unique_lock<std::mutex> lock(mtx);
        pool.push(obj);
        lock.unlock();
        cv.notify_one(); // wake one waiting thread
    }
};

void worker(ObjectPool<Task>& pool, int task_id) {
    auto task = pool.acquire();  // Get task from pool
    task->execute(task_id);      // Do work
    pool.release(task);          // Return to pool
}

int main() {
    ObjectPool<Task> pool(2); // Pool has only 3 Task objects

    std::vector<std::thread> threads;

    // Launch 10 threads, but only 3 tasks can be used at a time
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(worker, std::ref(pool), i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
