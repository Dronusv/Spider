#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <queue>
#include <mutex>

//�������� �� ��� ����������� ���

template<typename T>
class URLQueue {
public:
	void push(const T& value);//������� ������
	bool pop(T& result);//����������
	void wait_and_pop(T& result); //����� ���� � ������� ��������� �������
	bool empty();

private:
	std::queue<T> queue_; // ������� ������ � ������� �� �������
	std::mutex mutex_;                                 
	std::condition_variable cond_var_;              //��������� ������                      
};

