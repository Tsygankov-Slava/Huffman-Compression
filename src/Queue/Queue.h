#pragma once

#include <memory>
#include <string>

class Node {
public:
    std::string symbol;
    std::shared_ptr<Node> next = nullptr;
    std::shared_ptr<Node> prev = nullptr;

public:
    explicit Node(std::string symbol) : symbol(std::move(symbol)){};
};

class Queue {
    std::shared_ptr<Node> head = nullptr;
    std::shared_ptr<Node> tail = nullptr;

public:
    void push(const std::string &symbol);
    void pop();
    int size();
    bool empty();
};
