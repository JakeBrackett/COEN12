#include <iostream>


struct Node{
    int data;
    Node *next;
    Node *prev;
};

class Deque{
    int count;
    Node *head;
public:
    Deque();
    ~Deque();
    int size() { return count; } //O(1) returns the size of the deque
    void addFirst(int x);
    void addLast(int x);
    int removeFirst();
    int removeLast();
    int getFirst();
    int getLast();
};