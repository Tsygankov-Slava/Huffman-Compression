#include "File.h"

bool File::sortFunc(const std::pair<char, int> &a, const std::pair<char, int> &b) {
    return a.second > b.second;
}

bool File::readFile() {
    std::ifstream file(pathIn);
    if (!file) {
        std::cout << "Файл " << pathIn << " не найден. Посмотрите справочную информация (обратитесь с флагом --help).\n";
        return false;
    }
    std::string line;
    while (getline(file, line)) {
        for (auto const &symbol : line) {
            frequencyDictionary[symbol]++;
        }
    }
    frequencyDictionarySorted = {frequencyDictionary.begin(), frequencyDictionary.end()};
    std::sort(frequencyDictionarySorted.begin(), frequencyDictionarySorted.end(), sortFunc);
    return true;
}

void File::printFrequencyDictionary() {
    for (const auto &i : frequencyDictionarySorted) {
        std::cout << i.first << " -> " << i.second << "\n";
    }
}