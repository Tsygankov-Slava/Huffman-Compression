#include "CLI/CLI.h"
#include "File/File.h"
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

    auto file = File(cli.flags.at("--in").value, cli.flags.at("--out").value);
    file.readFile();
    file.printFrequencyDictionary();

    std::cout << "-------\n";

    auto tree = Tree(file);
    std::map<char, std::string> symbolsCode = tree.getSymbolsCode();
    tree.printSymbolsCode();
    return 0;
}
