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

void getNumbers(DEQUE *maindeque, int *max);
void radixSort(DEQUE *maindeque, DEQUE **radixarray, int max);

//O(n*k) with the radixSort function as the longest operation
int main(int argc, char * argv[]){
    DEQUE *radixarray[RADIXSIZE], *maindeque;
    int i, number, max, mainitems;
    maindeque = createDeque();
    for(i = 0; i < RADIXSIZE; i++)
        radixarray[i] = createDeque();
    getNumbers(maindeque, &max);
    radixSort(maindeque, radixarray, max);
    mainitems = numItems(maindeque);
    system("clear");
    for(i = 0; i < mainitems; i++){
        number = removeLast(maindeque);
        printf("%d\n", number);
    }
    destroyDeque(maindeque);
    for(i = 0; i < RADIXSIZE; i++){
        destroyDeque(radixarray[i]);
    }
    return 0;
}


//Gets the numbers from the user
// O(n) n being the number of items the user enters
void getNumbers(DEQUE *maindeque, int *max){
    int x;
    *max = 0;
    printf("Enter numbers to sort, type s to stop:\n");
    while(scanf("%d", &x) == 1){
        if(x < 0){
            printf("%d not accepted, enter positive numbers only or s to stop\n", x);
            continue;
        }
        addLast(maindeque, x);
        if(*max < x) *max = x;
    }
}
//implements the radix sorting algo
//O(n*k) n being the number of items to be sorted and k being the number of significant digits of the largest number
void radixSort(DEQUE *maindeque, DEQUE **radixarray, int max){
    int sigdigits, number, i, j, m, radixindex, mainitems, arritems, power = 1;
    mainitems = numItems(maindeque);
    sigdigits = ceil(log(max + 1)/log(RADIXSIZE));
    for(i = 0; i < sigdigits; i++){
        for(j = 0; j< mainitems; j++){
            number = removeLast(maindeque);
            radixindex = ((number)/(power)) % RADIXSIZE;
            addFirst(radixarray[radixindex], number);
        }
        power *= RADIXSIZE;
        
        for(j = 0; j < RADIXSIZE; j++){
            arritems = numItems(radixarray[j]);
            for(m = 0; m < arritems; m++){
                number = removeLast(radixarray[j]);
                addFirst(maindeque, number);
            }
        }
    }
}

