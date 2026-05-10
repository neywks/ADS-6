// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* head;
    int count;

public:
    TPQueue() : head(nullptr), count(0) {}

    ~TPQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const T& item) {
        Node* newNo = new Node(item);

        if (head == nullptr || item.prior > head->data.prior) {
            newNo->next = head;
            head = newNo;
            count++;
            return;
        }

        Node* current = head;
        while (current->next != nullptr &&
            current->next->data.prior >= item.prior) {
            current = current->next;
        }
        newNo->next = current->next;
        current->next = newNo;
        count++;
    }

    T pop() {
        if (head == nullptr) {
            throw "Queue is empty";
        }
        T res = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return res;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }
};

struct SYM {
    char ch;
    int prior;
};

#endif 
