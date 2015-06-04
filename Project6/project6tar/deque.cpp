#include <iostream>
#include <cassert>
#include "deque.h"


//Constructor
//O(1)
Deque::Deque(){
    count = 0;
    head = new Node;
    head->next = head;
    head->prev = head;
}

//Destructor
//O(n)
Deque::~Deque(){
    Node *np, *next;
    np = head;
    
    do {
        next = np->next;
        delete np;
        np = next;
    } while (np != head);
}

//Adds node to the start of deque
//O(1)void Deque::addFirst(int x){
    Node *np = new Node;
    np->data = x;
    count++;
    
    np->prev = head;
    np->next = head->next;
    
    head->next->prev = np;
    head->next = np;
}

//adds node to back of deque
//O(1)
void Deque::addLast(int x){
    Node *np = new Node;
    np->data = x;
    count++;
    
    np->prev = head->prev;
    np->next = head;
    
    head->prev->next = np;
    head->prev = np;
}

//deletes the first node in the list after the dummy and returns its data
//O(1)
int Deque::removeFirst(){
    int x;
    Node *np;
    assert(count > 0);
    count--;
    
    np = head->next;
    head->next = np->next;
    np->next->prev = head;
    
    x = np->data;
    delete np;
    return x;
}

// deletes the last node in the list and returns the data from it
// O(1)
int Deque::removeLast(){
    int x;
    Node *np;
    assert(count > 0);
    count--;
    
    np = head->prev;
    head->prev = np->prev;
    np->prev->next = head;
    
    x = np->data;
    delete np;
    return x;
}

//returns the data of the first node
// O(1)
int Deque::getFirst(){
    assert(count > 0);
    return head->next->data;
}

//returns the data of the last node
//O(1)
int Deque::getLast(){
    assert(count > 0);
    return head->prev->data;
}

