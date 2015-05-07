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

void destroyDeque(DEQUE *dp){
    NODE *np;
    assert(dp != NULL);
    np = dp->head;
    while(np->next != dp->head){
        np = np->next;
        free(np->prev);
    }
    free(np);
    free(dp);
}

int numItems(DEQUE *dp){
    assert(dp != NULL);
    return dp->count;
}

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

int removeFirst(DEQUE *dp){
    NODE *np;
    int data;
    assert(dp != NULL);
    np = dp->head->next;        //np is the node to be deleted
    data = np->data;            //store the data in np to be returned
    np->next->prev = dp->head;  //the node after np is the first node in the list, its prev pointer should be head
    dp->head->next = np->next;  //set head's next pointer to the node after np
    free(np);
    dp->count--;
    return data;
}

int removeLast(DEQUE *dp){
    NODE *np;
    int data;
    assert(dp != NULL);
    np = dp->head->prev;        //np is the node to be deleted
    data = np->data;            //store the data in np to be returned
    np->prev->next = dp->head;  //the node before np is the last node in the list, its next pointer should be head
    dp->head->prev = np->prev;  //set head's prev pointer to the node before np
    free(np);
    dp->count--;
    return data;
}

int getFirst(DEQUE *dp){
    assert(dp != NULL && dp->count != 0);
    return dp->head->next->data;
}

int getLast(DEQUE *dp){
    assert(dp != NULL && dp->count != 0);
    return dp->head->prev->data;
}

