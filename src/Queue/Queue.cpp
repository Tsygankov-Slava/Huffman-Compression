#include "Queue.h"

void Queue::push(const std::shared_ptr<NodeTree> &symbol) {
    std::shared_ptr<NodeQueue> node = std::make_shared<NodeQueue>(symbol);
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
    std::shared_ptr<NodeQueue> root = tail;
    while (root != head) {
        ++size;
        root = root->next;
    }
    return size;
}
