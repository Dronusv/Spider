
#include <iostream>
#include "boost/locale.hpp"
#include <sstream>
#include "Indexator.h"
#include <algorithm>

void Indexator::clearSTR(std::string& html)
{
	std::regex style_regex(R"(<style[^>]*>[\s\S]*?</style>)");
	html = std::regex_replace(html, style_regex, " ");

	// 2. ������� <script>...</script>
	std::regex script_regex(R"(<script[^>]*>[\s\S]*?</script>)");
	html = std::regex_replace(html, script_regex, " ");

	// 3. ������� ��� HTML-����
	std::regex tags_regex(R"(<[^>]+>)");
	html = std::regex_replace(html, tags_regex, " ");

	// 4. ����� ������������� ������ ��� inline-����� ������ �����, ���� ����.
	// ��������, ���� ���� style="display:none;"
	// ���������� ���������: style="[^"]*"
	std::regex style_attr_regex(R"(\s*style="[^"]*" )");
	html = std::regex_replace(html, style_attr_regex, " ");

	std::regex non_word_regex(R"([^A-Za-z0-9�-��-���]+)");
	html = std::regex_replace(html, non_word_regex, " ");

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

void Indexator::sendDataBase(BD& data_base, std::string url)
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
