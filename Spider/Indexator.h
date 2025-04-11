#pragma once
#include <regex>
#include <map>
#include <string>
#include <fstream>
#include "BD.h"


class Indexator {
public:
	void clearSTR(std::string& str);
	void lowerCase(std::string& str);
	void countwords(std::string& str);
	void sendDataBase(BD data_base,std::string url);
	
	void addURLS();







	//отладка
	void PrintWordCount() {
		for (auto c : wordcount) {
			std::cout << c.first << " " << c.second<<"\n";
		}
	}
private:
	int minchar=3;
	int maxchar=32;
	std::map<std::string, int> wordcount;
};