
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;

public:
    ThreadPool(size_t threads) : stop(false) {
        // Create 'threads' number of worker threads
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;

                    // Lock and fetch task from queue
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);

                        // Wait until task is available or stop signal is sent
                        this->condition.wait(lock, [this]() {
                            return this->stop || !this->tasks.empty();
                        });

                        // Exit if stop and no tasks
                        if (this->stop && this->tasks.empty())
                            return;

                        // Get task from queue
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    // Execute task
                    task();
                }
            });
        }
    }

    // Add new task to the pool
    void enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.push(std::move(task));
        }
        condition.notify_one();  // Notify a thread
    }

    // Gracefully shut down the pool
    ~ThreadPool() {
        stop = true;
        condition.notify_all();

        for (std::thread &worker : workers)
            worker.join();
    }
};

int main() {
    ThreadPool pool(2); // 4 worker threads

    // Enqueue 10 tasks
    for (int i = 0; i < 10; ++i) {
        pool.enqueue([i]() {
            std::cout << "Task " << i << " " << std::this_thread::get_id() << " is being processed\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }

    // Wait for destructor to clean up
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
