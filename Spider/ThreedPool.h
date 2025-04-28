#pragma once
#include "URLQueue.h"
#include <vector>
#include <functional>

class ThreadPool {
public:
	ThreadPool(size_t num_threads); //заполнение массива потоков и их подключение

	~ThreadPool();

	//добавление задачи
	void enqueue(std::function<void()> task);

	//остановка работы потоков
	void stop();
private:
	void worker();

	std::vector<std::thread> workers_;//массив потоков
	std::queue<std::function<void()>> tasks_; //массив задач
	std::mutex queue_mutex_;
	std::condition_variable cond_var_;
	bool stop_flag_;
	
};
