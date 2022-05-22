#pragma once

#include <fstream>
#include <bitset>

#include "../FrequencyDictionary/FrequencyDictionary.h"
#include "../Tree/Tree.h"

class OutputFile {
    FrequencyDictionary frequencyDictionary;
    Tree tree;

public:
    explicit OutputFile(FrequencyDictionary frequencyDictionary, Tree tree)
        : frequencyDictionary(std::move(frequencyDictionary)), tree(std::move(tree)) {
        writing();
    };
    void writing();
};
