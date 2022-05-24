#include "Queue.h"

void Queue::print() {
    auto root = tail;
    while (root != nullptr) {
        std::cout << root->symbol->symbol.second << " ";
        root = root->next;
    }
    std::cout << "\n";
}

void Queue::moveElement() {
    auto el = tail;
    auto compEl = el->next;
    while (el != nullptr && compEl != nullptr && el->symbol->symbol.second < compEl->symbol->symbol.second) {
        if (el == tail) {
            tail = compEl;
        }
        if (compEl == head) {
            head = el;
        }
        auto root = el;
        compEl->prev = el->prev;
        if (el->prev != nullptr) {
            el->prev->next = compEl;
        }
        el->next = compEl->next;
        el->prev = compEl;
        if (compEl->next != nullptr) {
            compEl->next->prev = el;
        }
        compEl->next = root;

        if (el->next != nullptr) {
            compEl = el->next;
        } else {
            break;
        }
    }
}

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
    moveElement();
    print();
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
