#include "CLI/CLI.h"
#include "Decoder/Decoder.h"
#include "FrequencyDictionary/FrequencyDictionary.h"
#include "OutputFile/OutputFile.h"
#include "Tree/Tree.h"

int main(int argc, char *argv[]) {
/*    auto queue = Queue();
    queue.push(std::make_shared<NodeTree>(std::make_pair('a', 1)));
    queue.push(std::make_shared<NodeTree>(std::make_pair('b', 2)));
    queue.push(std::make_shared<NodeTree>(std::make_pair('c', 3)));*/
    auto cli = CLI(argc, argv)
            .flag("--help")
            .flag("--description")
            .flag("--in", true, true)
            .flag("--out", true, true)
            .flag("--dec", false, true);

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
        std::cout << "-------\n";
        auto outFile = OutputFile(frequencyDictionary, tree);
        auto decoder = Decoder(frequencyDictionary.pathOut);
    } catch (const std::invalid_argument &error) {
        std::cout << error.what() << "\n";
        return 1;
    }

    return 0;
}
