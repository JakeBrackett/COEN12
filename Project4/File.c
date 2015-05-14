//
//  radix.c
//
//
//  Created by Jacob Brackett on 5/14/15.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "deque.h"

#define RADIXSIZE 10

DEQUE *getNumbers(DEQUE *maindeque, int *max);
DEQUE *radixSort(DEQUE *maindeque, DEQUE **radixarray, int max);

//O(n)
int main(int argc, char * argv[]){
    DEQUE *radixarray[RADIXSIZE], *maindeque, *sorted;
    int i, x, max, items;
    maindeque = createDeque();
    sorted = createDeque();
    for(i = 0; i < RADIXSIZE; i++)
        radixarray[i] = createDeque();
    getNumbers(maindeque, &max);
    sorted = radixSort(maindeque, radixarray, max);
    items = numItems(sorted);
    for(i = 0; i < items; i++){
        x = removeFirst(sorted);
        printf("%d\n", x);
    }
    destroyDeque(maindeque);
    destroyDeque(sorted);
    for(i = 0; i < RADIXSIZE; i++){
        destroyDeque(radixarray[i]);
    }
    return 0;
}


//Gets the numbers from the user
// O(n) n being the number of numbers the user enters
DEQUE* getNumbers(DEQUE *maindeque, int *max){
    int x;
    *max = 0;
    printf("Enter numbers to sort, type q to quit: ");
    while(scanf("%d", &x) == 1){
        if(x < 0){
            printf("Enter positive numbers only");
            continue;
        }
        addLast(maindeque, x);
        printf("%d", getLast(maindeque));
        if(*max < x) *max = x;
    }
    return maindeque;
}
//implements the radix sorting algo
//O(n)
DEQUE *radixSort(DEQUE *maindeque, DEQUE **radixarray, int max){
    int sigdigits, x, i, j, m, radixindex, numitems, items;
    sigdigits = (int) ceil(log(max+1)/log(RADIXSIZE));
    numitems = numItems(maindeque)
    for(i = 0; i < sigdigits; i++){
        for(j = 0; j < numitems; j++){
            x = removeFirst(maindeque);
            radixindex = ((int)x / (int)pow(10, i)) % 10;
            addLast(radixarray[radixindex], x);
        }
        for(j = 0; j < RADIXSIZE; j++){
            items = numItems(radixarray[j]);
            for(m = 0; m < items; m++){
                x = removeFirst(radixarray[j]);
                addLast(maindeque, x);
            }
        }
    }
    return maindeque;
}

