//
//  hash.c
//
//
//  Created by Jacob Brackett on 4/8/15.
//
//
#define EMPTY 0
#define FILLED 1
#define DELETED 2

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "set.h"

typedef struct set {
    int count;
    int length;
    char ** elts;
    char *flags;
} SET;

//mallocs space for a set, ititializes it and returns a pointer to the set
// O(n)
SET *createSet(int maxElts){
    SET *sp;
    int i;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->elts = malloc(sizeof(char *) * maxElts);
    assert(sp->elts != NULL);
    sp->flags = malloc(sizeof(char)*maxElts);
    assert(sp->flags != NULL);
    for(i=0;i<maxElts;i++)
        sp->flags[i] = EMPTY;
    return sp;
}

//frees the memory associated with a SET and the elts in it
// O(n)
void destroySet(SET *sp){
    int i;
    assert(sp != NULL);
    for(i = 0; i < sp->count; i++){
        free(sp->elts[i]);
    }
    free(sp->elts);
    free(sp->flags);
    free(sp);
}

// hashes a value and returns a key
// O(k) where k is the number of characters in the string
unsigned hashString(char *s){
    unsigned hash = 0;

    while (*s != '\0') {
        hash = 31 * hash + *s++;
    }
    return hash;
}

// Finds a element in the hash table. If it sets found to true, it returns the index of the element. If it sets find to false, it returns the location where the element should go in the hash table
//0(n) worst case, best case O(1)
static int findElement(SET *sp, char *elt, bool *found){
    unsigned hashedloc, i, probe, first_deleted = -1;
    hashedloc = hashString(elt) % sp->length;
    for(i = 0; i < sp->length; i++){
        probe = ((i + hashedloc) % sp->length);
        if(sp->flags[probe] == EMPTY){
            *found = false;
            if(first_deleted == -1) return probe;
            else return first_deleted;
        }
        
        else if(sp->flags[probe] == DELETED){
            if(first_deleted == -1)
                first_deleted = probe;
            continue;
        }
        
        else if(sp->flags[probe] == FILLED){
            if(strcmp(elt, sp->elts[probe]) == 0){
                *found = true;
                return probe;
            }
            else continue;
        }
    }
    // loop teminated with no empty spaces. Returns slot of first deleted element, or -1 if there were no deleted spaces.
    *found = false;
    return first_deleted;
}


//returns the number of Elements in a set
// O(1)
int numElements(SET *sp){
    assert(sp != NULL);
    return sp->count;
}

//returns true if elt is found in the set sp
//0(n) worst case, best case O(1)
bool hasElement(SET *sp, char *elt){
    bool found;
    assert(sp != NULL && elt != NULL);
    findElement(sp, elt, &found);
    return found;
}

// adds elt to SET sp in the correct spot if elt is not already there and there is space in the set, returns true if the operation was successful
//0(n) worst case, best case O(1)
bool addElement(SET *sp, char *elt){
    int i, index;
    bool found;
    assert(sp != NULL && elt != NULL);
    index = findElement(sp, elt, &found);
    if(found || index == -1)
        return false;
    elt = strdup(elt);
    assert(elt != NULL);
    sp->count++;
    sp->elts[index] = elt;
    sp->flags[index] = FILLED;
    return true;
}

//Removes an element from a set, returns true if element was removed
//0(n) worst case, best case O(1)
bool removeElement(SET *sp, char *elt){
    int index;
    bool found;
    assert(sp != NULL && elt != NULL);
    index = findElement(sp, elt, &found);
    if(!found) return false;
    free(sp->elts[index]);
    sp->flags[index] = DELETED;
    sp->count--;
    return true;
}



