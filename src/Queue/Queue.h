#pragma once

#include <memory>
#include <string>

#include "../Tree/Tree.h"

class NodeTree;

class NodeQueue {
public:
    std::shared_ptr<NodeTree> symbol;
    std::shared_ptr<NodeQueue> next = nullptr;
    std::shared_ptr<NodeQueue> prev = nullptr;

public:
    explicit NodeQueue(std::shared_ptr<NodeTree> symbol) : symbol(std::move(symbol)){};
};

class Queue {
public:
    std::shared_ptr<NodeQueue> head = nullptr;
    std::shared_ptr<NodeQueue> tail = nullptr;

public:
    void push(const std::shared_ptr<NodeTree> &symbol);
    void pop();
    int size();
};
