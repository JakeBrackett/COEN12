//
//  radix2.c
//  
//
//  Created by Jacob Brackett on 5/16/15.
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

int main(int argc, char *argv[]){
    DEQUE *maindeque, *radixarray[RADIXSIZE];
    int i, j, m, data, number, max = 0, mainitems, arritems, sigdigits, power = 1, radixindex;
    maindeque = createDeque();
    for(i = 0; i < RADIXSIZE; i++){
        radixarray[i] = createDeque();
    }
    
    printf("Enter Numbers to sort, anything else to quit:\n");
    while(scanf("%d", &data) == 1){
        if(data < 0){
            printf("Enter positive numbers only");
            continue;
        }
        addFirst(maindeque, data);
        if(max < data) max = data;
    }
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
    mainitems = numItems(maindeque);
    for(i = 0; i < mainitems; i++){
        number = removeLast(maindeque);
        printf("\n%d", number);
    }
    destroyDeque(maindeque);
    for(i = 0; i < RADIXSIZE; i++){
        destroyDeque(radixarray[i]);
    }
    return 0;
}