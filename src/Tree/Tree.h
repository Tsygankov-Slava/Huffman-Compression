#pragma once

#include <map>
#include <memory>

#include "../File/File.h"
#include "../Queue/Queue.h"

class Queue;

class NodeTree {
public:
    std::pair<char, int> symbol;
    std::shared_ptr<NodeTree> left;
    std::shared_ptr<NodeTree> right;

    explicit NodeTree(std::pair<char, int> symbol, std::shared_ptr<NodeTree> left = nullptr, std::shared_ptr<NodeTree> right = nullptr)
        : symbol(std::move(symbol)), left(std::move(left)), right(std::move(right)){};
};

class Tree {
    std::shared_ptr<Queue> queue = std::make_shared<Queue>();
    File file;
    std::shared_ptr<NodeTree> head = nullptr;

public:
    explicit Tree(File &file) : file(file){};
    void fillQueue();
    void createNode();
private:
};
