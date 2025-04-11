
#include <iostream>
#include "boost/locale.hpp"
#include <sstream>
#include "Indexator.h"


void Indexator::clearSTR(std::string& str)
{
	const std::regex pattern("\\<.*?\\>");  // ��������� ������� �������� �� ����� �������!!! ���������� ���������

	str = regex_replace(str, pattern, "");      // ������ � ��� ��� ������ �� ""
}

void Indexator::lowerCase(std::string& str)
{

	//�������� ����� ������ ����� ��� ����� ������
	boost::locale::generator gen;
	std::locale loc = gen("en_US.UTF-8"); // �������� �� ������ ������
	std::locale::global(loc);
	std::cout.imbue(loc);
	// ���������� ���� 
	str = boost::locale::to_lower(str);

}

void Indexator::countwords(std::string& str)            // �� ���� ����� ����� ������� ��������� ��������� ��� ��� ��������
{
	std::stringstream stream(str);
	std::string word;
	while (stream >> word) {
		if (word.length() > 3 && word.length() < 32) {             //������� ������ 
			wordcount[word]++;
		}
	}
	
}

void Indexator::sendDataBase(BD data_base, std::string url)
{
	data_base.insert_URL(url);
	for (auto c : wordcount) {
		data_base.insert_word(c.first);
		data_base.insert_count_word_URL(c.second, data_base.get_id_word(c.first), data_base.get_id_URL(url));    //�������� ����� �������� ��������� ��� ���������� �������
	}
}

void Indexator::addURLS()
{
}
