//
//  huffman.c
//  
//
//  Created by Jacob Brackett on 5/23/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "pack.h"
#include "tree.h"

#define p(x) (((x)-1)/2) //returns parent location
#define l(x) ((x)*2+1)   //returns left location
#define r(x) ((x)*2 + 2) //returns right location


void charCount(FILE *fp);
void createNodes(void);
void insert(struct tree *leaf);
struct tree *delete(void);
void printcode(struct tree *np);

int counts[257];
struct tree *leaves[257]; //all children
struct tree *heap[257]; // priority queue
int heapcount = 0;


int main(int argc, char *argv[]){
    FILE *fp;
    struct tree *l, *r;
    int i;
    if(argc != 3){
        fprintf(stderr, "Usage: huffman file-to-compress file-output\n");
        exit(255);
    }
    if((fp = fopen(argv[1], "rb")) == NULL){
        fprintf(stderr, "Please provide a valid path to file to compress\n");
        exit(255);
    }
    charCount(fp);
    fclose(fp);
    createNodes();
    while(heapcount > 1){
        l = delete();
        r = delete();
        insert(createTree(getData(l) + getData(r), l, r));
    }
    for(i = 0; i < 256; i++){
        if(leaves[i] != NULL){
           if(isprint(i))
               printf("\nCharacter: %c ", i);
            else
                printf("'%03o' ", i);
          
            printf("Appeared: %d time(s) Code: ", getData(leaves[i]));
            printcode(leaves[i]);
            printf("\n");
        }
    }
    
    pack(argv[1], argv[2], leaves);
    
    return 0;
}

void charCount(FILE *fp){
    int x;
    while((x = fgetc(fp)) != EOF){
        counts[x]++;
    }
}

void createNodes(void){
    int i;
    for(i = 0; i < 257; i++){
        if(counts[i] == 0){
            leaves[i] = NULL;
            continue;
        }
        leaves[i] = createTree(counts[i], NULL, NULL);
        insert(leaves[i]);
    }
    leaves[256] = createTree(0, NULL, NULL);
    insert(leaves[256]);
}


void insert(struct tree *leaf){
    int idx;
    assert(leaf != NULL);
    //heap[heapcount++] = leaf;
    idx = heapcount++;
    while(getData(leaf) < getData(heap[p(idx)])){
        heap[idx] = heap[p(idx)];
        idx = p(idx);
    }
    heap[idx] = leaf;
}

struct tree *delete(void){
  /*  int min = 0, i;
    for(i = 0; i < heapcount; i++){
        if(getData(heap[min]) > getData(heap[i]))
            min = i;
    }
    heap[heapcount] = heap[min];
    heap[min] = heap[--heapcount];
    return heap[heapcount+1]; */
    struct tree *np, *min;
    int idx = 0, child;
    min = heap[0];
    np = heap[heapcount-1];
    while(l(idx) < heapcount){
        child = l(idx);
        if(r(idx) < heapcount && getData(heap[l(idx)]) > getData(heap[p(idx)]))
            child = r(idx);
        if(getData(np) > getData(heap[child])){
            heap[idx] = heap[child];
            idx = child;
        }
        else
            break;
    }
    heap[idx] = np;
    heapcount--;
    return min;
}

void printcode(struct tree *np){
    if(getParent(np) != NULL) {
        printcode(getParent(np));
        printf("%d", np == getLeft(getParent(np)));
    }
}


