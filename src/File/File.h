#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * Класс File производит работу с файлом и заполняет частотный словарь
 */
class File {
    std::string pathIn; /** Переменная хранит путь к файлу, который надо сжать */
    std::string pathOut; /** Переменная хранит путь к файлу, который получится на выходе */
    std::map<char, int> frequencyDictionary; /** частотный словарь */
    std::vector<std::pair<char, int>> frequencyDictionarySorted; /** отсортированный (по кол-ву символов) частотный словарь */

public:
    explicit File(std::string pathIn, std::string pathOut) : pathIn(std::move(pathIn)), pathOut(std::move(pathOut)){};
    bool readFile();
    void printFrequencyDictionary();

private:
    static bool sortFunc(const std::pair<char, int> &a, const std::pair<char, int> &b);
};
