#include "Tree.h"

/*
 * The fillQueue function fills the initial queue from the nodes of the tree
 */
void Tree::fillQueue() {
    for (const auto &map : frequencyDictionary.frequencyDictionarySorted) {
        std::shared_ptr<NodeTree> node = std::make_shared<NodeTree>(map);
        queue.push(node);
    }
}

/*
 * The createNode function creates nodes for the tree in the order of the queue
 */
void Tree::createNode() {
    while (queue.size() != 1) {
        std::shared_ptr<NodeTree> newNodeLeft = queue.front();
        queue.pop();
        std::shared_ptr<NodeTree> newNodeRight = queue.front();
        queue.pop();
        std::shared_ptr<NodeTree> newNode =
                std::make_shared<NodeTree>(std::make_pair('\0', newNodeLeft->symbol.second + newNodeRight->symbol.second),
                                           newNodeLeft, newNodeRight);
        queue.push(newNode);
    }
    head = queue.front();
}

/*
 * The createSymbolsCode function goes through the tree and creates its own code for each character
 */
void Tree::createSymbolsCode(const std::shared_ptr<NodeTree> &node, const std::string &code) {
    char symbol = node->symbol.first;
    if (symbol != '\0') {
        symbolsCode[symbol] = code;
        return;
    }
    createSymbolsCode(node->left, code + "1");
    createSymbolsCode(node->right, code + "0");
}

void Tree::printSymbolsCode() {
    for (const auto &[symbol, countSymbol] : symbolsCode) {
        std::cout << symbol<< " -> " << countSymbol << "\n";
    }
}

std::map<char, std::string> Tree::getSymbolsCode() {
    fillQueue();
    createNode();
    createSymbolsCode(head);
    return symbolsCode;
}
