#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <typeinfo>
#include<exception>
#include <variant>
#include <cstdlib>
class ini_parser
{
private:
    std::map <std::string, std::map<std::string, std::string>> m;
    std::string get_v(std::string name);
public:
    ini_parser(std::string filename);
    void print();
    template<typename T>
    T get_value(std::string name) {
        return get_v(name);
    }
    template<>
    int get_value(std::string name) {
        return std::stoi(get_v(name));
    }
    template<>
    double get_value(std::string name) {
        return std::stod(get_v(name));
    }
};
