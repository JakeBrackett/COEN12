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
#include "tree.h"

int *charcount(FILE *fp, int characters[]);

int main(int argc, char *argv[]){
    int characters[26];
    FILE *ifp, *ofp;
    if(argc != 3){
        fprintf(stderr, "Usage: huffman file-to-compress file-output");
    }
    if((ifp = fopen(argv[1], "r")) == NULL)
        fprintf(stderr, "Please provide a valid path to file to compress");
    if((ofp = fopen(argv)[2], "w")) == NULL){
        fprintf(stderr, "Please provide a valid path to file to store compressed file");
    }
    charcount(fp, characters);
}

int *charcount(FILE *fp, int characters[]){
    int i, x;
    char ochar;
    while(ochar = fgetc(fp) != EOF){
        x = tolower(ochar);
        x = x - 'a';
        characters[x]++;
    }
    return characters;
}