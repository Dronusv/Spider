#include "ini_parser.h"

std::string ini_parser::get_v(std::string name)
{
    std::string sec;
    std::string val;
    int count = 0;
    for (int i = 0; i < name.size(); ++i) {
        if (count != 0) {
            val.push_back(name[i]);
        }
        if (name[i] == '.') {
            ++count;
        }
        if (count == 0) {
            sec.push_back(name[i]);
        }

    }
    if (m[sec][val] == "") {
        throw std::exception("No value for this variable");
    }
    return m[sec][val];
}

ini_parser::ini_parser(std::string filename)
{
    std::ifstream file(filename);
    std::string str;
    std::string key;
    while (std::getline(file, str)) {
        std::string name = "";
        std::string val = "";
        int key_count = 0;
        int namecount = 0;
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == ';') {
                break;
            }
            if (str[i] == '[') {
                key = "";
                ++key_count;
            }
            if (str[i] == ']') {
                --key_count;
            }
            if (key_count == 1 && str[i] != '[') {
                key.push_back(str[i]);
            }
            if (key_count == 0) {
                if (namecount == 1) {
                    val.push_back(str[i]);
                }
                if (str[i] == '=') {
                    ++namecount;
                }
                if (namecount == 0 && str[i] != ']' && str[i] != ' ') {
                    name.push_back(str[i]);
                }

            }


        }
        m[key];
        if (name != "") {
            m[key][name] = val;
        }
    }
    if (file.is_open() == false) {
        throw std::exception("Wrong file name!");
    }
    file.close();
}

void ini_parser::print()
{
    for (auto c : m) {
        std::cout << c.first << "\n";
        for (auto d : c.second) {
            std::cout << d.first << " " << d.second << "\n";
        }
    }
}
