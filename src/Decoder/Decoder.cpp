#include "Decoder.h"

void Decoder::readData() {
    file.open(path, std::ifstream::binary);
    unsigned char countSymbolsCode = 0;
    file.read(reinterpret_cast<char *>(&countSymbolsCode), sizeof countSymbolsCode);
    std::cout << "Size: " << (int) countSymbolsCode << "\n";

    int i = 0;
    while (i < (int) countSymbolsCode) {
        unsigned char symbol;
        std::string code;
        file.read(reinterpret_cast<char *>(&symbol), sizeof symbol);
        file.read(reinterpret_cast<char *>(&code), sizeof code);
        ++i;
        std::cout << symbol << " : " << code << "\n";
        frequencyDictionary[code] = symbol;
    }
    file.read(reinterpret_cast<char *>(&byteCount), sizeof byteCount);
    file.read(reinterpret_cast<char *>(&remains), sizeof remains);
    std::cout << "byteCount: " << (int) byteCount << "\n";
    std::cout << "remains: " << (int) remains << "\n";
}

void Decoder::decode() {
    std::string code;
    int i = 0;
    for (; i < byteCount; ++i) {
        unsigned char byte;
        file.read(reinterpret_cast<char *>(&byte), sizeof byte);
        std::bitset<CHAR_BIT> b(byte);
        code += b.to_string();
    }
    if (remains > 0) {
        unsigned char byte;
        file.read(reinterpret_cast<char *>(&byte), sizeof byte);
        std::bitset<CHAR_BIT> b(byte);
        code += b.to_string().substr(CHAR_BIT - remains, CHAR_BIT);
    }
    //std::cout << code << "\n";

    std::string symbolCode;
    for (int j = 0; j < code.size(); ++j) {
        symbolCode += code[j];
        if (frequencyDictionary.count(symbolCode)) {
            text += frequencyDictionary[symbolCode];
            symbolCode = "";
        }
    }
    //std::cout << text;
    std::ofstream fileOut(path+".dec");
    fileOut << text;
}