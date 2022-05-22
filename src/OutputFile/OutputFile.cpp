#include "OutputFile.h"


void OutputFile::writing() {
    std::string textBin;
    auto fd = frequencyDictionary;
    std::ofstream file(fd.pathOut, std::ofstream::binary);
    unsigned char size = fd.frequencyDictionary.size();
    file.write(reinterpret_cast<char*>(&size), sizeof size);
    for (const auto &symbolCode : tree.symbolsCode) {
        file.write(reinterpret_cast<const char*>(&symbolCode.first), sizeof symbolCode.first);
        file.write(reinterpret_cast<const char*>(&symbolCode.second), sizeof symbolCode.second);
    }
    for (const auto &line : fd.lines) {
        for (const auto &symbol : line) {
            textBin += tree.symbolsCode[symbol];
        }
    }
    //std::cout << textBin << "\n";
    unsigned long byteCount = textBin.size() / CHAR_BIT;
    unsigned long remains = textBin.size() % CHAR_BIT;
    std::cout << byteCount << " " << remains << "\n";
    file.write(reinterpret_cast<const char*>(&byteCount), sizeof byteCount);
    file.write(reinterpret_cast<const char*>(&remains), sizeof remains);

    int i = 0;
    for (; i < byteCount; ++i) {
        std::bitset<CHAR_BIT> b(textBin.substr(i * CHAR_BIT, CHAR_BIT));
        auto value = static_cast<unsigned char>(b.to_ulong());
        file.write(reinterpret_cast<char *>(&value), sizeof value);
    }
    if (remains > 0) {
        std::bitset<CHAR_BIT> b(textBin.substr(i * CHAR_BIT, remains));
        auto value = static_cast<unsigned char>(b.to_ulong());
        file.write(reinterpret_cast<char *>(&value), sizeof value);
    }
}