#include "TaskManager.h"
#include "curl/curl.h"
		
void TaskManager::Task(std::string& url)
{
	CURL* curl;
	CURLcode res;
	std::string htmlContent;

	curl_global_init(CURL_GLOBAL_DEFAULT); // ������������� libcurl
	curl = curl_easy_init(); // ������������� ������

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url); // ������� ��� URL
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // ������� ������� ��������� ������
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent); // ������� ������ ��� ������ ������
		res = curl_easy_perform(curl); // ���������� �������

		// �������� �� ������
		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			index.clearSTR(htmlContent);
			index.lowerCase(htmlContent);
			index.countwords(htmlContent);
			index.PrintWordCount();
			//std::cout << htmlContent << std::endl; // ����� ����������� HTML

		}

		curl_easy_cleanup(curl); // �������
	}

	curl_global_cleanup(); // ���������� ������ � libcurl
   

}

TaskManager::TaskManager(size_t numThreads) : pool(numThreads) {

}

void TaskManager::enqueue(const std::string& item) {
    tasks.push(item);

    // ���������� ������ �� ���������� � ��� �������
	boost::asio::post(pool, [this]() {
		std::string item;
		auto strPtr = std::make_shared<std::string>(item);
		if (tasks.pop(item)) {
			Task(*strPtr); // ��������� ������
		}
		});
}

TaskManager::~TaskManager() {
    pool.join(); // ���� ���������� ���� ����� � ����
}