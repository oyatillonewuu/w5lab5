#include <iostream>
#include "ldlist.h"
using namespace std;

void IntLinkedList::removeFront() {
    if (empty()) return;
    IntNode* tmp = head;
    head = head->next;
    delete tmp;
}

void IntLinkedList::removeBack() {
    if (empty()) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    IntNode* prev = head;
    IntNode* target = head->next;

    while (target->next) {
        prev = target;
        target = target->next;
    }

    delete target;
    prev->next = nullptr;
}

int IntLinkedList::removeAll(int x) {
    if (empty()) return 0;
    int count = 0;

    // Remove x's at front
    while (head && head->elem == x) {
        IntNode* tmp = head;
        head = head->next;
        delete tmp;
        count++;
    }

    // If head becoms empty or head
    // originally was a single node.
    if (!head || !(head->next)) {
        return count;
    }

    // The above loop guarantees we now
    // don't have any x at front.
    IntNode* prev = head;
    IntNode* mover = head->next;

    while (mover) {
        if (mover->elem == x) {
            prev->next = mover->next;
            delete mover;
            mover = prev->next;
            count++;
            continue;
        }
        prev = mover;
        mover = mover->next;
    }
    return count;
}

void IntLinkedList::reverse() {
    if (empty() || head->next == nullptr) return;

    IntNode* prev = head;
    IntNode* current = head->next;
    head->next = nullptr;

    while (current) {
        IntNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}

/*
 *
 *  0->1->2->3
 *
 * Loop:
 *  prePrev = null
 *  prev = 0
 *  current = 1
 *
 *  next = current->next = 2
 *  current -> next = prev;
 *  prev->next = prePrev;
 *
 *  prePrev = prev;
 *  prev = current;
 *  current = next;
 *
 * */
