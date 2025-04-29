#pragma once

#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <Windows.h>


//скорее всего понадобиться правило 5

class BD {
public:
	
	void createBD();

	void connectBD(std::string conn_str);

	void insert_URL(std::string URL);
	void insert_word(std::string word);
	void insert_count_word_URL(int count, int id_word, int id_URL);

	bool existsWord(const std::string& word);
	//void update_count_word_URL(int count, int id_word, int id_URL);
	
	int get_id_URL(std::string URL);
	int get_id_word(std::string word);



	~BD() {
		delete conn_ptr;
	}

	
private:
	//std::string conn_str;
	pqxx::connection* conn_ptr = NULL;
	


};
