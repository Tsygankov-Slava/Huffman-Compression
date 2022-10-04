#include "Decoder.h"

void Decoder::readData() {
    file.open(pathIn, std::ifstream::binary);
    unsigned char countSymbolsCode = 0;
    file.read(reinterpret_cast<char *>(&countSymbolsCode), sizeof countSymbolsCode);

    int i = 0;
    if (isPrintSteps) {
        std::cout << "Code of the symbols:";
    }
    while (i < (int) countSymbolsCode) {
        unsigned char symbol;
        std::string code;
        file.read(reinterpret_cast<char *>(&symbol), sizeof symbol);
        file.read(reinterpret_cast<char *>(&code), sizeof code);
        ++i;
        if (isPrintSteps) {
            std::cout << symbol << " -> " << code << "\n";
        }
        frequencyDictionary[code] = symbol;
    }
    if (isPrintSteps) {
        std::cout << "\nPROCESS...\n";
    }
    file.read(reinterpret_cast<char *>(&byteCount), sizeof byteCount);
    file.read(reinterpret_cast<char *>(&remains), sizeof remains);
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

    std::string symbolCode;
    for (const char &symbol : code) {
        symbolCode += symbol;
        if (frequencyDictionary.count(symbolCode)) {
            text += frequencyDictionary[symbolCode];
            symbolCode = "";
        }
    }
    std::ofstream fileOut(pathOut);
    fileOut << text;
}