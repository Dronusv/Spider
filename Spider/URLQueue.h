#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <queue>
#include <mutex>

//проверка на уже добавленный урл

template<typename T>
class URLQueue {
public:
	void push(const T& value);//добвить ссылку
	bool pop(T& result);//извлечение
	void wait_and_pop(T& result); //ждать пока в очереди появиться элемент
	bool empty();

private:
	std::queue<T> queue_; // хранить ссылку и уровень ее глубины
	std::mutex mutex_;                                 
	std::condition_variable cond_var_;              //уведомить потоки                      
};

