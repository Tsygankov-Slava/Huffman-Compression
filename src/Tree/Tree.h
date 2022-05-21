#pragma once

#include <map>
#include <memory>

#include "../File/File.h"
#include "../Queue/Queue.h"

class Queue;

/**
 * Класс NodeTree описывает узел дерева
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
 * Класс Tree описывает дерево символов, которое построено на основе частотного словаря
 */
class Tree {
public:
    File file;
    std::shared_ptr<Queue> queue = std::make_shared<Queue>();
    std::shared_ptr<NodeTree> head = nullptr;
    std::map<char, std::string> symbolsCode;

public:
    explicit Tree(File &file) : file(file){};
    std::map<char, std::string> getSymbolsCode();
    void printSymbolsCode();

private:
    void fillQueue();
    void createNode();
    void createSymbolsCode(const std::shared_ptr<NodeTree> &node, const std::string &code = "");
};
