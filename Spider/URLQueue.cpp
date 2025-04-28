#include "URLQueue.h"



template<typename T>
void URLQueue<T>::push(const T& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(value);
    cond_var_.notify_one();
}

template<typename T>
bool URLQueue<T>::pop(T& result)
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        return false;
    }
    result = std::move(queue_.front());
    queue_.pop();
    return true;
    
}

template<typename T>
void URLQueue<T>::wait_and_pop(T& result)
{
    std::unique_lock<std::mutex> lock(mutex_);
    cond_var_.wait(lock, [this] { return !queue_.empty(); });
    result = std::move(queue_.front());
    queue_.pop();
}

template<typename T>
bool URLQueue<T>::empty()
{
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}




