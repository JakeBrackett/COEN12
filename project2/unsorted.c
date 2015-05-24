//
//  set.c
//  
//
//  Created by Jacob Brackett on 4/8/15.
//
//

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
} SET;

//mallocs space for a set, ititializes it and returns a pointer to the set
// O(1)
SET *createSet(int maxElts){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->elts = malloc(sizeof(char *) * maxElts);
    assert(sp->elts != NULL);
    return sp;
}

//frees the memory associated with a SET and the elts in it
// O(1)
void destroySet(SET *sp){
    int i;
    assert(sp != NULL);
    for(i = 0; i < sp->count; i++){
        free(sp->elts[i]);
    }
    free(sp->elts);
    free(sp);
}

//private function to search a SET for a specific elt
// O(n)
static int findElement(SET *sp, char *elt){
    int i;
    for(i=0; i<sp->count;i++){
        if(strcmp(elt, sp->elts[i]) == 0)
            return i;
    }
    return -1;
}

//returns the number of Elements in a set
// O(1)
int numElements(SET *sp){
    assert(sp != NULL);
    return sp->count;
}

//returns true if elt is found in the set sp
// O(n)
bool hasElement(SET *sp, char *elt){
    assert(sp != NULL && elt != NULL);
    return findElement(sp,elt) != -1;
}

// adds elt to SET sp if elt is not already there and there is space in the set, returns true if the operation was successful
// O(n)
bool addElement(SET *sp, char *elt){
    assert(sp != NULL && elt != NULL);
    if(findElement(sp,elt) != -1 || sp->count == sp->length)
        return false;
    elt = strdup(elt);
    assert(elt != NULL);
    sp->elts[sp->count++] = elt;
    return true;
}

//Removes an element from a set, returns true if element was removed
// O(n)
bool removeElement(SET *sp, char *elt){
    int index;
    assert(sp != NULL && elt != NULL);
    index = findElement(sp, elt);
    if(index == -1)
        return false;
    free(sp->elts[index]);
    sp->elts[index] = sp->elts[sp->count-1];
    sp->count--;
    return true;
}



