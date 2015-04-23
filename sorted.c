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
// O(n)
void destroySet(SET *sp){
    int i;
    assert(sp != NULL);
    for(i = 0; i < sp->count; i++){
        free(sp->elts[i]);
    }
    free(sp->elts);
    free(sp);
}

//private function to search a SET for a specific elt using binary search.
// if found == true it returns the index of the value
// if found == false it returns where the value should go
// O(log n)
static int findElement(SET *sp, char *elt, bool *found){
    int lo, hi, mid, dif;
    lo = 0;
    hi = sp->count-1;
    while(lo<=hi){
        mid = (lo+hi)/2;
        dif = strcmp(elt, sp->elts[mid]);
        if(dif < 0)
            hi = mid -1;
        else if(dif > 0)
            lo = mid + 1;
        else{
            *found = true;
            return mid;
        }
    }
    *found = false;
    return lo;
}

//returns the number of Elements in a set
// O(1)
int numElements(SET *sp){
    assert(sp != NULL);
    return sp->count;
}

//returns true if elt is found in the set sp
// O(log n)
bool hasElement(SET *sp, char *elt){
    bool found;
    assert(sp != NULL && elt != NULL);
    findElement(sp, elt, &found);
    return found;
}

// adds elt to SET sp in the correct spot if elt is not already there and there is space in the set, returns true if the operation was successful
// O(n) + O(log n) = O(n)
bool addElement(SET *sp, char *elt){
    int i, index;
    bool found;
    assert(sp != NULL && elt != NULL);
    index = findElement(sp, elt, &found);
    if(found || sp->count == sp->length)
        return false;
    elt = strdup(elt);
    assert(elt != NULL);
    sp->count++;
    for(i = sp->count; i > index; i--){
        sp->elts[i] = sp->elts[i-1];
    }
    sp->elts[index] = elt;
    return true;
}

//Removes an element from a set, returns true if element was removed
// O(n) + O(log n) = O(n)
bool removeElement(SET *sp, char *elt){
    int index, i;
    bool found;
    assert(sp != NULL && elt != NULL);
    index = findElement(sp, elt, &found);
    if(!found) return false;
    free(sp->elts[index]);
    for(i = index; i < sp->count-1; i++)
        sp->elts[i] = sp->elts[i+1];
    sp->count--;
    return true;
}



