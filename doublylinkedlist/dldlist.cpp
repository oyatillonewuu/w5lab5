#include <iostream>
#include "dldlist.h"
using namespace std;


DoublyLinkedList::DoublyLinkedList() {
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
}

DoublyLinkedList::~DoublyLinkedList() {
    while (header) {
        Node* tmp = header;
        header = header->next;
        delete tmp;
    }
}

bool DoublyLinkedList::empty() const {
    return header->next == trailer;
}

int DoublyLinkedList::size() const {
    if (header->next == trailer) return 0;
    int count = 0;
    Node* mover = header->next;
    while (mover->next) {
        count++;
        mover = mover->next;
    }
    return count;
}

int DoublyLinkedList::front() const {
    if (header->next == trailer) return -1; // actually, UB
    return header->next->value;
}

int DoublyLinkedList::back() const {
    if (trailer->prev == header) return -1; // actually, UB
    return trailer->prev->value;
}

void DoublyLinkedList::addFront(int value) {
    add(header, value);
}

void DoublyLinkedList::addBack(int value) {
    add(trailer->prev, value);
}

void DoublyLinkedList::removeFront() {
    remove(header->next);
}

void DoublyLinkedList::removeBack() {
    remove(trailer->prev);
}

bool DoublyLinkedList::isPalindrome() const {
    if (header->next == trailer) return true; // vacuously

    Node* left = header->next;
    Node* right = trailer->prev;

    while (left != right) {
        if (left->value != right->value) return false;
        if (left->next == right) break;
        left = left->next;
        right = right->prev;
    }
    return true;
}

void DoublyLinkedList::add(Node* v, const int& value) {
    if (v == nullptr ||
        (v->next == nullptr && v->prev == nullptr) ||
        v == trailer
    ) return; // Actually, UB

    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = v->next;
    newNode->prev = v;
    v->next->prev = newNode;
    v->next = newNode;
}

void DoublyLinkedList::remove(Node* v) {
    if (
        v == nullptr ||
        v == trailer ||
        v == header ||
        (v->next == nullptr && v->prev == nullptr)
    ) return; // Actually, UB

    v->prev->next = v->next;
    v->next->prev = v->prev;
    delete v;
}

void DoublyLinkedList::print() const {
    if (header->next == trailer) {
        cout << "Empty.\n";
    }
    Node* mover = header->next;
    while (mover->next) {
        cout << mover->value << " ";
        mover = mover->next;
    }
    cout << endl;
}


/*
*
* head = tail
*
* [null] addBack
*      trailer->next = new;
*      new->prev = trailer;
*      trailer=new;
*      if trailer was null:
*          head = new;
*          trailer = new;
*
*      Again:
*          head [n1] trailer
*          addFront
*
*          new->next = head;
*          head->prev = new;
*
*          head = new;
*
*          addBack
*
*      removeFront:
*          head [n1] trailer;
*
*          this case:
*              head = null;
*              trailer = null;
*
*          otherwise:
*              [n1]<->[n2]
*
*              head->next->prev = null;
*              head = head->next;
*
*      removeBack:
*          if head == trailer == null:
*              error
*          elif head == trailer:
*              head = null;
*              trailer = null;
*          else:
*              trailer->prev->next = null;
*              trailer = trailer->prev;
*
*
* Sentinel nodes
*
* header = <-null->
* trailer = header;
*
* addBack:
*      newNode;
*      prev = trailer->prev;
*      newNode->prev = trailer->prev;
*      trailer->prev->next = newNode;
*      trailer->prev = newNode;
*
*      Yea! Sentinel nodes seem to simplify the process!
*
* addFront:
*      newNode;
*      header->next->prev = newNode;
*      newNode->next=  header->next;
*      header->next = newNode;
*
* removeBack:
*      if trailer->prev == header:
*          error
*      trailer->prev->prev->next = trailer;
*      trailer->prev = trailer->prev->prev;
*
* removeFront:
*      if header->next = trailer:
*          error
*      header->next->next->prev = header;
*      header->next = header->next->next;
*
* add(Node* v, value)
*      newNode(v)
*   v == null: error
*   newNode->prev = v;
*   newNode->next = v->next;
*   v->next = newNode;
*   newnode->next->prev = newNode;
*
* remove Node* v
*
*   if v == header or trailer: error
*
*   v->prev->next = v->next;
*   v->next->prev = v->prev;
**/
