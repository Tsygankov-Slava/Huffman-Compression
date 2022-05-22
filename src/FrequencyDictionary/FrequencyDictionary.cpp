#include "FrequencyDictionary.h"

bool FrequencyDictionary::readData() {
    std::ifstream file(pathIn);
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return true;
}

void FrequencyDictionary::buildDictionary() {
    for (auto const &line : lines) {
        for (auto const &symbol : line) {
            frequencyDictionary[symbol]++;
        }
    }
    frequencyDictionarySorted = {frequencyDictionary.begin(), frequencyDictionary.end()};
    std::sort(frequencyDictionarySorted.begin(), frequencyDictionarySorted.end(),
              [](const std::pair<char, int> &a, const std::pair<char, int> &b) {
                  return a.second < b.second;
              });
}

void FrequencyDictionary::print() {
    for (const auto &i : frequencyDictionarySorted) {
        std::cout << i.first << " -> " << i.second << "\n";
    }
}
