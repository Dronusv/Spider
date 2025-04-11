
#include <boost/asio.hpp>
#include <boost/lockfree/queue.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Indexator.h"


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

// ���������� ����� ��� ���������
const int NUM_STRINGS = 100;
const int NUM_THREADS = 4;    // ���������� ������� � ����




// �����, ������� ��������� �������� � �������������� ���� �������
class TaskManager {
public:
    
    TaskManager(size_t numThreads);

    void enqueue(const std::string& item);

    ~TaskManager();

private:
    void Task(std::string& str);
    boost::asio::thread_pool pool; // ��� �������
    boost::lockfree::queue<std::string> tasks{ NUM_STRINGS }; // ������� ������
    Indexator index;
};

