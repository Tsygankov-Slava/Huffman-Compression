#pragma once

#include <map>
#include <memory>

#include "../FrequencyDictionary/FrequencyDictionary.h"
#include "../Queue/Queue.h"

class Queue;

/**
 * The Node Tree class describes a tree node
 */
class NodeTree {
public:
    std::pair<char, int> symbol;
    std::shared_ptr<NodeTree> left;
    std::shared_ptr<NodeTree> right;

    explicit NodeTree(std::pair<char, int> symbol, std::shared_ptr<NodeTree> left = nullptr, std::shared_ptr<NodeTree> right = nullptr)
        : symbol(std::move(symbol)), left(std::move(left)), right(std::move(right)){};
};

/*
 * The Tree class describes a symbol tree that is built on the basis of a frequency dictionary
 */
class Tree {
public:
    FrequencyDictionary frequencyDictionary;
    std::shared_ptr<Queue> queue = std::make_shared<Queue>();
    std::shared_ptr<NodeTree> head = nullptr;
    std::map<char, std::string> symbolsCode;

public:
    explicit Tree(FrequencyDictionary &frequencyDictionary) : frequencyDictionary(frequencyDictionary){};
    std::map<char, std::string> getSymbolsCode();
    void printSymbolsCode();

private:
    void fillQueue();
    void createNode();
    void createSymbolsCode(const std::shared_ptr<NodeTree> &node, const std::string &code = "");
};
