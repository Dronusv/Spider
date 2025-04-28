#include "ThreedPool.h"

ThreadPool::ThreadPool(size_t num_threads) : stop_flag_(false)
{
    for (size_t i = 0; i < num_threads; ++i) {
        workers_.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        tasks_.push(task);
    }
    cond_var_.notify_one();
}

void ThreadPool::stop()
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        stop_flag_ = true;
    }
    cond_var_.notify_all();
    for (auto& t : workers_) {
        if (t.joinable()) t.join();
    }
}

void ThreadPool::worker()
{
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            cond_var_.wait(lock, [this] { return stop_flag_ || !tasks_.empty(); });
            if (stop_flag_ && tasks_.empty()) return;  // завершение
            task = std::move(tasks_.front());
            tasks_.pop();
        }
        task();
    }
}

