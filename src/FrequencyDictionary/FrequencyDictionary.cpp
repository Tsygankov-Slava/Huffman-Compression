#include "FrequencyDictionary.h"

bool FrequencyDictionary::readData() {
    std::ifstream file(pathIn);
    if (!file) {
        throw std::invalid_argument("Файл " + pathIn + " не найден. Посмотрите справочную информация (обратитесь с флагом --help).\n");
    }
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line + '\n');
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
