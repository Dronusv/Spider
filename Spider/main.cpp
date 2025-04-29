#include <iostream>
#include "ini_parser.h"
#include "BD.h"
#include "Indexator.h"
#include "Spider.h"


//проблема с ссылками (там говно а не ссылка)
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



		


















		

	}catch (std::exception& ex) {

		std::cout << ex.what();
	}
}

