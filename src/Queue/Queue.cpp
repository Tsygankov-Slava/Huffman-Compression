#include "Queue.h"

void Queue::push(const std::string &symbol) {
    Node *node = new Node(symbol);
    if (head == nullptr && tail == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->prev = node;
        node->next = tail;
        tail = node;
    }
}

void Queue::pop() {
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head->prev->next = nullptr;
        head = head->prev;
    }
}

int Queue::size() {
    if (head == nullptr && tail == nullptr) {
        return 0;
    }
    int size = 1;
    Node *root = tail;
    while (root != head) {
        ++size;
        root = root->next;
    }
    return size;
}

bool Queue::empty() {
    return size();
}