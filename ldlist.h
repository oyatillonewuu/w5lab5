#pragma once

class IntNode{
private:
    int elem;
    // was: string
    IntNode* next;
    friend class IntLinkedList;
};

class IntLinkedList{
private:
    IntNode* head;
public:
    IntLinkedList();
    ~IntLinkedList();
    bool empty() const;
    void addFront(int i);
    void addBack(int i);
    int size();
    void print();
    int sum();
    double average();

    // Problems
    
    void removeFront();
    void removeBack();
    int removeAll(int x); // returns the number of nodesremoved
    void reverse();
};

