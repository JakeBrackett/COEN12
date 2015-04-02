//
//  Jacob Brackett
//
//  count.c
//
// Description: This program takes a filepath from the command line and

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[]){
    FILE * finput;
    int count;
    char buffer[MAX_WORD_LENGTH+1];
    // check if correct arguments were used
    if(argc != 2){
        printf("Usage: count.c filepath\n");
        exit(255);
    }
    // Open file to finput
    if((finput = fopen(argv[1], "r")) == NULL){
        printf("Could not read %s. Try again.\n", argv[1]);
        exit(255);
    }
    // Reads file one word at a time. incrementing count each time
    while(fscanf(finput, "%s", buffer) != EOF){
        count++;
    }
    fclose(finput);
    printf("%d total words\n", count);
    return 0;
}