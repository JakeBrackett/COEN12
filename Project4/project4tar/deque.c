//
//  deque.c
//
//
//  Created by Jacob Brackett on 5/7/15.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "deque.h"

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct deque{
    int count;
    struct node *head;
} DEQUE;

//allocates space for a Deque
//O(1)
DEQUE *createDeque(void){
    DEQUE *dp;
    dp = malloc(sizeof(DEQUE));
    assert(dp != NULL);
    dp->head = malloc(sizeof(NODE));
    assert(dp->head != NULL);
    dp->head->next = dp->head;
    dp->head->prev = dp->head;
    dp->count = 0;
    return dp;
}

//frees all the nodes in the deque then the deque itself
//O(n)
void destroyDeque(DEQUE *dp){
    NODE *np;
    assert(dp != NULL);
    np = dp->head->next;
    while(np != dp->head){
        np = np->next;
        free(np->prev);
    }
    free(dp->head);
    free(dp);
}

//O(n)
int numItems(DEQUE *dp){
    assert(dp != NULL);
    return dp->count;
}

//Adds node to the start of deque
//O(1)
void addFirst(DEQUE *dp, int x){
    NODE *np, *dummy;
    assert(dp != NULL);
    np = malloc(sizeof(NODE));
    assert(np != NULL);
    np->data = x;
    np->prev = dp->head;        //the node goes after the head node
    np->next = dp->head->next;  //the node goes before the node after the head
    dp->head->next = np;        //set head's next pointer to new node
    np->next->prev = np;        //set the next node's prev pointer to new node
    dp->count++;
}

//adds node to back of deque
//O(1)
void addLast(DEQUE *dp, int x){
    NODE *np;
    assert(dp != NULL);
    np = malloc(sizeof(NODE));
    assert(np != NULL);
    np->data = x;
    np->next = dp->head;        //the list is circular; the tail's next should be the head
    np->prev = dp->head->prev;  //the node goes after the node currently after the head
    dp->head->prev = np;        //set head's prev pointer to new node
    np->prev->next = np;        //set the old tail node's next pointer to new node
    dp->count++;
}

//deletes the first node in the list after the dummy and returns its data
//O(1)
int removeFirst(DEQUE *dp){
    NODE *np;
    int data;
    assert(dp != NULL && dp->head->next != dp->head);
    np = dp->head->next;        //np is the node to be deleted
    data = np->data;            //store the data in np to be returned
    np->next->prev = dp->head;  //the node after np is the first node in the list, its prev pointer should be head
    dp->head->next = np->next;  //set head's next pointer to the node after np
    free(np);
    dp->count--;
    return data;
}

// deletes the last node in the list and returns the data from it
// O(1)
int removeLast(DEQUE *dp){
    NODE *np;
    int data;
    assert(dp != NULL && dp->head->prev != dp->head);
    np = dp->head->prev;        //np is the node to be deleted
    data = np->data;            //store the data in np to be returned
    np->prev->next = dp->head;  //the node before np is the last node in the list, its next pointer should be head
    dp->head->prev = np->prev;  //set head's prev pointer to the node before np
    free(np);
    dp->count--;
    return data;
}

//returns the data of the first node
// O(1)
int getFirst(DEQUE *dp){
    assert(dp != NULL && dp->count != 0);
    return dp->head->next->data;
}

//returns the data of the last node
//O(1)
int getLast(DEQUE *dp){
    assert(dp != NULL && dp->count != 0);
    return dp->head->prev->data;
}

