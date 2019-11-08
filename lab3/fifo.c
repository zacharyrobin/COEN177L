
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //gets the table size out of the arguments
int parseArguments(int argc, char *argv[]) {
    int tableSize;
    if(argc == 2 && (tableSize = atoi(argv[1]))) {
        return tableSize;
    }
    fprintf(stderr, "Wrong arguments. Pass tableSize as an argument\n");
    exit(-1);
}

//checks to see if the page (pageRequest) is in the cache (pagetable)
int isInMemory(int pageRequest, int *pageTable, int tableSize) {
    int i;
    for(i = 0; i < tableSize; i++) {
        if(pageRequest == pageTable[i]) {
            return 1;
        }
    }
    return 0;
}



int main(int argc, char *argv[]) {
    int tableSize = parseArguments(argc, argv);    
    int pageRequest, pageTableIndex = 0, numRequest = 0, numMisses = 0;
    int *pageTable = (int *) malloc(sizeof(int)*tableSize);

    FILE *fp; //input 
    char buff[255];
    fp = fopen("accesses.txt", "r");
    if(fp == NULL) {
        printf("Could not open file!");
        return 1;
    }

    FILE *wp; //file we are writing to as output
    wp = fopen("fifoOutput.txt", "w");



    //need to change this to the file that he gives us instead of null
    char *input = NULL;

    
    size_t inputAllocated = 0;
    size_t bytesRead;
    int oldest = 0; // this keeps track of what is the oldest one and needs to be replaced 
    char str[255]; //buffer read 


    while((fgets(str, 255, fp)) != 0) {
        pageRequest = atoi(str);        
        if(pageRequest == 0) {
            continue;
        }
        numRequest++;
        
        //if the page is not in the cache then increment the number of misses and implements FIFO
        if(!isInMemory(pageRequest, pageTable, tableSize)) {
            // printf("Page %d caused a page fault.\n", pageRequest);
            fprintf(wp, "Page %d caused a page fault.\n", pageRequest);
            
            numMisses++;
            if(pageTableIndex < tableSize) {
                pageTable[pageTableIndex++] = pageRequest;
            } else {
                // To store the pages in FIFO manner 
                int i;
                for(i=0; i <tableSize-1; i++){
                    pageTable[i] = pageTable[i+1];
                }
                pageTable[tableSize-1] = pageRequest;
                
                // pageTable[oldest] = pageRequest;
                // oldest++;
                // if(oldest > tableSize) {
                //     oldest = 0; // we are reseting the oldest page to be 0 so it loops around and doesnt go out of bounds 
                // }
            }
        } // else probably want to update something in pageTable so that lru and second chance work correctly
    }
    printf("Hit rate = %f\n", (numRequest-numMisses)/(double)numRequest);
    free(input);
    free(pageTable);

    //Closing the files
    fclose(fp);
    fclose(wp);
    return 0;
}
