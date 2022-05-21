#include "Tree.h"

void Tree::fillQueue() {
    for (const auto& map : file.frequencyDictionarySorted) {
        std::shared_ptr<NodeTree> node = std::make_shared<NodeTree>(map);
        queue->push(node);
    }
}

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