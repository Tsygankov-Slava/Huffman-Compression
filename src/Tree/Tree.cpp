#include "Tree.h"

/*
 * Функция fillQueue заполняет первоначальную очередь из узлов дерева
 */
void Tree::fillQueue() {
    for (const auto &map : file.frequencyDictionarySorted) {
        std::shared_ptr<NodeTree> node = std::make_shared<NodeTree>(map);
        queue->push(node);
    }
}

/*
 * Функция createNode создаёт узлы для дерева в порядке очереди
 */
void Tree::createNode() {
    while (queue->size() != 1) {
        std::shared_ptr<NodeTree> newNodeLeft = queue->head->symbol;
        queue->pop();
        std::shared_ptr<NodeTree> newNodeRight = queue->head->symbol;
        queue->pop();
        std::shared_ptr<NodeTree> newNode =
                std::make_shared<NodeTree>(std::make_pair(' ', newNodeLeft->symbol.second + newNodeRight->symbol.second),
                                           newNodeLeft, newNodeRight);
        queue->push(newNode);
    }
    head = queue->head->symbol;
}

/*
 * Функция createSymbolsCode проходится по дереву и создаёт для каждого символа свой код
 */
void Tree::createSymbolsCode(const std::shared_ptr<NodeTree> &node, const std::string &code) {
    char symbol = node->symbol.first;
    if (symbol != ' ') {
        symbolsCode[symbol] = code;
        return;
    }
    createSymbolsCode(node->left, code + "1");
    createSymbolsCode(node->right, code + "0");
}

void Tree::printSymbolsCode() {
    for (const auto &code : symbolsCode) {
        std::cout << code.first << " -> " << code.second << "\n";
    }
}

std::map<char, std::string> Tree::getSymbolsCode() {
    fillQueue();
    createNode();
    createSymbolsCode(head);
    printSymbolsCode();
    return symbolsCode;
}