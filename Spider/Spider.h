#pragma once
#include <string>
#include "ThreedPool.h"
#include <unordered_set	>
#include "BD.h"
#include "curl/curl.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

class Spider {
public:
	Spider(const std::string& start_url, int max_depth, size_t thread_count);
	~Spider();

	void connect_to_database(std::string conn_str);
	void create_data_base();
	
	void Start();	
private:

	std::string get_full_url(const std::string& url, const std::string& base_url);
	std::string get_base_url(const std::string& url);
	void add_url(const std::string& url, int depth);

	//обработка страницы 
	void process_page(const std::string& url, int depth);  //Тут будет создаваться индексатор 

	//получить хтмл страницы
	std::string fetch_page(const std::string& url); // тут будет работа через curlx`


	// возможно хранить бд
	BD data_base;
	std::string start_url_;
	int max_depth_;
	ThreadPool pool_;
	std::unordered_set<std::string> visited_; //посещенные ссылки
	std::mutex visited_mutex_;
	std::atomic<int> active_tasks_;  // счетчик активных задач
	
};