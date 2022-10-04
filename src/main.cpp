#include "CLI/CLI.h"
#include "Decoder/Decoder.h"
#include "FrequencyDictionary/FrequencyDictionary.h"
#include "OutputFile/OutputFile.h"
#include "Tree/Tree.h"

#include "../libs/cli.hpp"

void encode(cli::FlagsType &parsedFlags);
void decode(cli::FlagsType &parsedFlags);

int main(int argc, char *argv[]) {
    auto cli = cli::Cli();
    try {
        cli.command("encode", "This is the command that starts encoding the file with the Huffman algorithm.", "",
                    {
                            cli::Flag("input", "i", "Input file to be encoded.", true, true),
                            cli::Flag("output", "o", "Output file to be encoded. \n By default the compressed file will be written to the input file with the prefix \".enc\" at the end.", false, true),
                            cli::Flag("steps", "s", "Print the information about encode (the execution steps)", false, false),
                    },
                    encode)
                .command("decode", "This is the command that starts decoding the encoded file using the Huffman algorithm.", "",
                         {
                                 cli::Flag("input", "i", "Input file to be decoded", true, true),
                                 cli::Flag("output", "o", "Output file to be decoded. \n By default the compressed file will be written to the input file with the prefix \".dec\" at the end.", false, true),
                                 cli::Flag("steps", "s", "Print the information about decode (the execution steps)", false, false),
                         },
                         decode)
                .parse(argc, argv);
    } catch (const std::invalid_argument &error) {
        std::cout << error.what();
        return 2;
    }
    return 0;
}

void encode(cli::FlagsType &parsedFlags) {
    std::cout << "PROCESS...\n";
    const std::string pathIn = parsedFlags.at("input").value;
    const std::string pathOut = (parsedFlags.count("output")) ? parsedFlags.at("output").value : pathIn+".enc";
    auto frequencyDictionary = FrequencyDictionary(pathIn, pathOut);
    auto tree = Tree(frequencyDictionary);
    std::map<char, std::string> symbolsCode = tree.getSymbolsCode();
    if (parsedFlags.count("steps")) {
        std::cout << "Count of the symbols:\n";
        frequencyDictionary.print();
        std::cout << "-------\n\n";
        std::cout << "Code of the symbols:";
        tree.printSymbolsCode();
        std::cout << "-------\n\n";
    }
    auto outFile = OutputFile(frequencyDictionary, tree);
}

void decode(cli::FlagsType &parsedFlags) {
    std::string pathIn = parsedFlags.at("input").value;
    std::string pathOut = (parsedFlags.count("output")) ? parsedFlags.at("output").value : pathIn+".dec";
    auto decoder = Decoder(pathIn, pathOut, parsedFlags.count("steps"));
}
