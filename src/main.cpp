#include "CLI/CLI.h"
#include "FrequencyDictionary/FrequencyDictionary.h"
#include "Tree/Tree.h"

int main(int argc, char *argv[]) {
    auto cli = CLI(argc, argv)
                       .flag("--help")
                       .flag("--description")
                       .flag("--in", true, true)
                       .flag("--out", true, true);

    CLI::ParseState parseState = cli.parse();
    if (parseState == CLI::ParseState::WRONG) {
        return 1;
    }
    if (parseState == CLI::ParseState::EXIT) {
        return 0;
    }

    try {
        auto frequencyDictionary = FrequencyDictionary(cli.flags.at("--in").value, cli.flags.at("--out").value);
        frequencyDictionary.print();
        std::cout << "-------\n";
        auto tree = Tree(frequencyDictionary);
        std::map<char, std::string> symbolsCode = tree.getSymbolsCode();
        tree.printSymbolsCode();
    } catch (const std::exception &ex) {
        std::cout << ex.what() << "\n";
        std::cout << "Файл " << cli.flags.at("--in").value << " не найден. Посмотрите справочную информация (обратитесь с флагом --help).\n";
        return 1;
    }

    return 0;
}
