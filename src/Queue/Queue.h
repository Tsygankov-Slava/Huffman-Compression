#pragma once

#include <string>

class Node {
public:
    std::string symbol;
    Node *next = nullptr;
    Node *prev = nullptr;

public:
    explicit Node(std::string symbol) : symbol(std::move(symbol)){};
};

class Queue {
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    void push(const std::string &symbol);
    void pop();
    int size();
    bool empty();
};
