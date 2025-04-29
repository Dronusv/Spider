
#include <iostream>
#include "boost/locale.hpp"
#include <sstream>
#include "Indexator.h"
#include <algorithm>

void Indexator::clearSTR(std::string& html)
{
	std::regex style_regex(R"(<style[^>]*>[\s\S]*?</style>)");
	html = std::regex_replace(html, style_regex, " ");

	// 2. Удаляем <script>...</script>
	std::regex script_regex(R"(<script[^>]*>[\s\S]*?</script>)");
	html = std::regex_replace(html, script_regex, " ");

	// 3. Удаляем все HTML-теги
	std::regex tags_regex(R"(<[^>]+>)");
	html = std::regex_replace(html, tags_regex, " ");

	// 4. Можно дополнительно убрать все inline-стили внутри тегов, если есть.
	// Например, если есть style="display:none;"
	// Регулярное выражение: style="[^"]*"
	std::regex style_attr_regex(R"(\s*style="[^"]*" )");
	html = std::regex_replace(html, style_attr_regex, " ");

	std::regex non_word_regex(R"([^A-Za-z0-9А-Яа-яЁё]+)");
	html = std::regex_replace(html, non_word_regex, " ");

}

void Indexator::lowerCase(std::string& str)
{

	//уязвимое место скорее всего тут будут ошибки
	boost::locale::generator gen;
	std::locale loc = gen("en_US.UTF-8"); // Замените на нужную локаль
	std::locale::global(loc);
	std::cout.imbue(loc);
	// подключить буст 
	str = boost::locale::to_lower(str);

}

void Indexator::countwords(std::string& str)            // по идее слова после очистки разедлены пробелами так что прокатит
{
	std::stringstream stream(str);
	std::string word;
	while (stream >> word) {
		if (word.length() > 3 && word.length() < 32) {             //условие записи 
			wordcount[word]++;
		}
	}
	
}

void Indexator::sendDataBase(BD& data_base, std::string url)
{
	data_base.insert_URL(url);
	for (auto c : wordcount) {
		
		data_base.insert_word(c.first);
		data_base.insert_count_word_URL(c.second, data_base.get_id_word(c.first), data_base.get_id_URL(url));    //возможно стоит объявить перменные для сокращение строчки
	}
}

void Indexator::addURLS()
{
}
