#pragma once


class Node {
private:
    int value;
    Node* prev {nullptr};
    Node* next {nullptr};
    friend class DoublyLinkedList;
};

class DoublyLinkedList {
private:
    Node* header;
    Node* trailer;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    bool empty() const;
    int size() const;
    int front() const;
    int back() const;

    void addFront(int);
    void addBack(int);
    void removeFront();
    void removeBack();

    bool isPalindrome() const;
    void print() const;

protected:
    void add(Node* v, const int& e);
    void remove(Node* v);
};
