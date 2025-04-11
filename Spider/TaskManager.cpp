#include "TaskManager.h"
#include "curl/curl.h"
		
void TaskManager::Task(std::string& url)
{
	CURL* curl;
	CURLcode res;
	std::string htmlContent;

	curl_global_init(CURL_GLOBAL_DEFAULT); // Инициализация libcurl
	curl = curl_easy_init(); // Инициализация сессии

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url); // Укажите ваш URL
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Укажите функцию обратного вызова
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent); // Укажите строку для записи данных
		res = curl_easy_perform(curl); // Выполнение запроса

		// Проверка на ошибки
		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			index.clearSTR(htmlContent);
			index.lowerCase(htmlContent);
			index.countwords(htmlContent);
			index.PrintWordCount();
			//std::cout << htmlContent << std::endl; // Вывод полученного HTML

		}

		curl_easy_cleanup(curl); // Очистка
	}

	curl_global_cleanup(); // Завершение работы с libcurl
   

}

TaskManager::TaskManager(size_t numThreads) : pool(numThreads) {

}

void TaskManager::enqueue(const std::string& item) {
    tasks.push(item);

    // Отправляем задачу на выполнение в пул потоков
	boost::asio::post(pool, [this]() {
		std::string item;
		auto strPtr = std::make_shared<std::string>(item);
		if (tasks.pop(item)) {
			Task(*strPtr); // Обработка строки
		}
		});
}

TaskManager::~TaskManager() {
    pool.join(); // Ждем завершения всех задач в пуле
}