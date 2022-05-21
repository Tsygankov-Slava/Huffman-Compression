#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>


class File {
    std::string pathIn;
    std::string pathOut;
    std::map<char, int> frequencyDictionary;
    std::vector<std::pair<char, int>> frequencyDictionarySorted;

public:
    explicit File(std::string pathIn, std::string pathOut) : pathIn(std::move(pathIn)), pathOut(std::move(pathOut)){};
    bool readFile();
    void printFrequencyDictionary();

private:
    static bool sortFunc(const std::pair<char, int> &a, const std::pair<char, int> &b);
};
