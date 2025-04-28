#pragma once
#include "URLQueue.h"
#include <vector>
#include <functional>

class ThreadPool {
public:
	ThreadPool(size_t num_threads); //���������� ������� ������� � �� �����������

	~ThreadPool();

	//���������� ������
	void enqueue(std::function<void()> task);

	//��������� ������ �������
	void stop();
private:
	void worker();

	std::vector<std::thread> workers_;//������ �������
	std::queue<std::function<void()>> tasks_; //������ �����
	std::mutex queue_mutex_;
	std::condition_variable cond_var_;
	bool stop_flag_;
	
};
