#include <iostream>
#include "ldlist.h"
using namespace std;


IntLinkedList::IntLinkedList(): head(nullptr) {}
IntLinkedList::~IntLinkedList(){
    // My addition
    while (head) {
        IntNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

bool IntLinkedList::empty() const{
    return head == nullptr;
}

void IntLinkedList::addFront(int i){
    IntNode* n = new IntNode();
    n->elem = i;
    n->next = head;
    head = n;
}

void IntLinkedList::addBack(int i){
    IntNode *node = new IntNode();
    node->elem = i;
    node->next = nullptr;
    if(empty()){
        head = node;
        return;
    }
    IntNode *h = head;
    while(h->next != nullptr){
        h = h->next;
    }
    h->next = node;
}

int IntLinkedList::size() {
    IntNode* h = head;
    int count = 0;
    while(h != nullptr){
        count++;
        h = h->next;
    }
    return count;
}

void IntLinkedList::print(){
    IntNode *h = head;
    if(empty()){
        cout << "List is Empty!" << endl;
        return;
    }
    while(h!=nullptr){
        cout<< h->elem <<" ";
        h = h->next;
    }
}

int IntLinkedList::sum() {
    IntNode* h = head;
    int sum = 0;
    while(h!=nullptr){
        sum = sum + h->elem;
        h = h->next;
    }
    return sum;
}

double IntLinkedList::average(){
    return double(sum()) / size();
}
