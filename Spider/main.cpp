#include <iostream>
#include "ini_parser.h"
#include "BD.h"
#include "Indexator.h"
#include "Spider.h"


//работ с бд (ошика при добавление уже существующего слова)
//

using namespace std;

//проверить работу класса бд
struct BDconfig {
	std::string host;
	std::string port;
	std::string nameBD;
	std::string username;
	std::string userpassword;
};


//size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
//	size_t totalSize = size * nmemb;
//	userp->append((char*)contents, totalSize);
//	return totalSize;
//}



int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	try {
		BDconfig conf;
		ini_parser pars("C:/Users/PC/Desktop/Project c++/Spider/test.txt");                     //починить короткий путь 
		conf.host = pars.get_value<std::string>("Database.hostBD");
		conf.port = pars.get_value<std::string>("Database.portBD");
		conf.nameBD = pars.get_value<std::string>("Database.nameBD");
		conf.username = pars.get_value<std::string>("Database.username");
		conf.userpassword = pars.get_value<std::string>("Database.userpassword");
		std::string str_conn=("dbname="+conf.nameBD+" "
			"host=" + conf.host + " "
			"port=" + conf.port + " "
			"user=" + conf.username + " "
			"password="+ conf.userpassword);                                                  
		
		std::string starturl = pars.get_value<std::string>("URLs.startURL");

		Spider spider(starturl,2,1);
		spider.connect_to_database(str_conn);
		spider.create_data_base();
		spider.Start();


		
		




		


















		//TEST CURL

		//CURL* curl;
		//CURLcode res;
		//std::string htmlContent;
		//
		//curl_global_init(CURL_GLOBAL_DEFAULT); // Инициализация libcurl
		//curl = curl_easy_init(); // Инициализация сессии
		//
		//if (curl) {
		//	curl_easy_setopt(curl, CURLOPT_URL, "ссылка"); // Укажите ваш URL
		//	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Укажите функцию обратного вызова
		//	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent); // Укажите строку для записи данных
		//	res = curl_easy_perform(curl); // Выполнение запроса
		//
		//	// Проверка на ошибки
		//	if (res != CURLE_OK) {
		//		std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		//	}
		//	else {
		//		Index.clearSTR(htmlContent);
		//		Index.lowerCase(htmlContent);
		//		Index.countwords(htmlContent);
		//		Index.PrintWordCount();
		//		//std::cout << htmlContent << std::endl; // Вывод полученного HTML
		//		
		//	}
		//
		//	curl_easy_cleanup(curl); // Очистка
		//}
		//
		//curl_global_cleanup(); // Завершение работы с libcurl
		//return 0;
	
		

	}catch (std::exception& ex) {
		
		std::cout << ex.what();
	}
}

