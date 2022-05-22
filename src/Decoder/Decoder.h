#pragma once

#include <map>
#include <string>

#include "../FrequencyDictionary/FrequencyDictionary.h"
#include "../Tree/Tree.h"

class Decoder {
    std::string path;
    std::map<std::string, unsigned char> frequencyDictionary;
    std::ifstream file;
    std::string text;
    unsigned long byteCount = '\0';
    unsigned long remains = '\0';


public:
    explicit Decoder(std::string &path) : path(std::move(path)) {
        readData();
        decode();
    };
    void readData();
    void decode();
};