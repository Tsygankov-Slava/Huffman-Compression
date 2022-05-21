#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * Класс FrequencyDictionary производит работу с файлом и заполняет частотный словарь
 */
class FrequencyDictionary {
    std::string pathIn;  /** Переменная хранит путь к файлу, который надо сжать */
    std::string pathOut; /** Переменная хранит путь к файлу, который получится на выходе */
    std::vector<std::string> lines;
    std::map<char, int> frequencyDictionary; /** частотный словарь */

public:
    std::vector<std::pair<char, int>> frequencyDictionarySorted; /** отсортированный (по кол-ву символов) частотный словарь */

public:
    explicit FrequencyDictionary(std::string pathIn, std::string pathOut)
        : pathIn(std::move(pathIn)), pathOut(std::move(pathOut)) {
        readData();
        buildDictionary();
    };
    bool readData();
    void buildDictionary();
    void print();
};
