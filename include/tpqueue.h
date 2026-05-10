// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
template<typename T>
class TPQueue {
 private:
  struct Node {
      T data;
      Node* next;
  };

  Node* head;
  size_t count;

  Node* CreateNode(const T& value, Node* nextNode = nullptr) {
      Node* temp = new Node;
      temp->data = value;
      temp->next = nextNode;
      return temp;
  }

 public:
    TPQueue(): head(nullptr), count(0) {}

    TPQueue(const TPQueue& other): count(other.count) {
        Node* cur = other.head;
        while (cur != nullptr) {
            push(cur->data);
            cur = cur->next;
        }
    }

    TPQueue(const TPQueue&& other) : head(other.head), count(other.count) {
        other.head = nullptr;
        other.count = 0;
    }

    TPQueue& operator=(const TPQueue&& other) {
        if (this != &other) {
            clear();
            head = other.head;
            count = other.count;
            other.head = nullptr;
            other.count = 0;
        }
        return *this;
    }

    TPQueue& operator=(const TPQueue& other) {
        if (this != &other) {
            clear();
            Node* cur = other.head;
            while (cur != nullptr) {
                push(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    ~TPQueue() {
        clear();
    }

    void push(const T& value) {
        Node* newNode = CreateNode(value);
        if (head == nullptr || value.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            ++count;
            return;
        }

        Node* cur = head;
        while (cur->next != nullptr && cur->next->data.prior >= value.prior) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        ++count;
    }

    T pop() {
        if (head == nullptr) {
            throw std::out_of_range("Pqueue is empty");
        }
        Node* oldHead = head;
        T result = oldHead->data;
        head = head->next;
        delete oldHead;
        --count;
        return result;
    }

    void clear() {
        while (head != nullptr) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        count = 0;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
