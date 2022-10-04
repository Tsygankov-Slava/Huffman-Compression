#pragma once

#include <map>
#include <string>
#include <utility>

#include "../FrequencyDictionary/FrequencyDictionary.h"
#include "../Tree/Tree.h"

class Decoder {
    std::string pathIn;
    std::string pathOut;
    std::map<std::string, unsigned char> frequencyDictionary;
    std::ifstream file;
    std::string text;
    unsigned long byteCount = '\0';
    unsigned long remains = '\0';
    bool isPrintSteps = false;


public:
    explicit Decoder(std::string &pathIn, std::string &pathOut, bool isPrintSteps) : pathIn(std::move(pathIn)), pathOut(std::move(pathOut)), isPrintSteps(isPrintSteps) {
        std::cout << "PROCESS...\n";
        readData();
        decode();
    };

    ~Decoder() {
        std::cout << "File decoding is completed! \n";
    }

    void readData();
    void decode();
};