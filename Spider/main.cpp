#include <iostream>
#include "ini_parser.h"
#include "BD.h"
#include "Indexator.h"


//
//����������� ���������������� ������� ������
// ��� ������� 
//���������� ���������!!!

using namespace std;

//��������� ������ ������ ��
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
	try {
		BDconfig conf;
		ini_parser pars("C:/Users/PC/Desktop/Project c++/Spider/test.txt");                     //�������� �������� ���� 
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
		BD data_base;
		data_base.connectBD(str_conn);
		//data_base.createBD(conn);

		


		
		




		


















		//TEST CURL

		//CURL* curl;
		//CURLcode res;
		//std::string htmlContent;
		//
		//curl_global_init(CURL_GLOBAL_DEFAULT); // ������������� libcurl
		//curl = curl_easy_init(); // ������������� ������
		//
		//if (curl) {
		//	curl_easy_setopt(curl, CURLOPT_URL, "������"); // ������� ��� URL
		//	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // ������� ������� ��������� ������
		//	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent); // ������� ������ ��� ������ ������
		//	res = curl_easy_perform(curl); // ���������� �������
		//
		//	// �������� �� ������
		//	if (res != CURLE_OK) {
		//		std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		//	}
		//	else {
		//		Index.clearSTR(htmlContent);
		//		Index.lowerCase(htmlContent);
		//		Index.countwords(htmlContent);
		//		Index.PrintWordCount();
		//		//std::cout << htmlContent << std::endl; // ����� ����������� HTML
		//		
		//	}
		//
		//	curl_easy_cleanup(curl); // �������
		//}
		//
		//curl_global_cleanup(); // ���������� ������ � libcurl
		//return 0;
	
		

	}catch (std::exception& ex) {
		std::cout << ex.what();
	}
}

