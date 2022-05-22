#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>


/**
 * The Frequency Dictionary class works with the file and fills in the frequency dictionary
 */
class FrequencyDictionary {
public:
    std::string pathIn;             /** the path to the file to compress */
    std::string pathOut;            /** the path to the output file */
    std::vector<std::string> lines; /** vector of file lines */
    std::map<char, int> frequencyDictionary;

public:
    std::vector<std::pair<char, int>> frequencyDictionarySorted; /** sorted (by number of characters) frequency dictionary */

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
