
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //gets the table size out of the arguments
int parseArguments(int argc, char *argv[])
{
    int tableSize;
    if (argc == 2 && (tableSize = atoi(argv[1])))
    {
        return tableSize;
    }
    fprintf(stderr, "Wrong arguments. Pass tableSize as an argument\n");
    exit(-1);
}

//checks to see if the page (pageRequest) is in the cache (pagetable)
int isInMemory(int pageRequest, int *pageTable, int tableSize)
{
    int i;
    for (i = 0; i < tableSize; i++)
    {
        if (pageRequest == pageTable[i])
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int tableSize = parseArguments(argc, argv);
    int pageRequest, pageTableIndex = 0, numRequest = 0, numMisses = 0, totalPages = 0;
    int *pageTable = (int *)malloc(sizeof(int) * tableSize);
    int *refPageTable = (int *)malloc(sizeof(int) * tableSize);

    FILE *fp; //input
    char buff[255];
    fp = fopen("accesses.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file!");
        return 1;
    }

    FILE *wp; //file we are writing to as output
    wp = fopen("scOutput.txt", "w");

    //need to change this to the file that he gives us instead of null
    char *input = NULL;

    size_t inputAllocated = 0;
    size_t bytesRead;
    int oldest = 0; // this keeps track of what is the oldest one and needs to be replaced
    char str[255];  //buffer read

    while ((fgets(str, 255, fp)) != 0)
    {
        pageRequest = atoi(str);
        if (pageRequest == 0)
        {
            continue;
        }
        numRequest++;

        //if the page is not in the cache then increment the number of misses and implements FIFO
        if (!isInMemory(pageRequest, pageTable, tableSize))
        {
            printf("Page %d caused a page fault.\n", pageRequest);
            fprintf(wp, "Page %d caused a page fault.\n", pageRequest);
            numMisses++;
            if (totalPages < tableSize - 1)
            { //if the table isn't full, we can insert directly into the array
                totalPages++;
                pageTable[pageTableIndex] = pageRequest;
                refPageTable[pageTableIndex] = 0;
                pageTableIndex = (pageTableIndex + 1) % tableSize; //use circular array, in case we need to wrap around to the beginning of the array
            }
            else
            { //if the table is full and the page doesn't already exist in the array, we need to replace the oldest one
                while (refPageTable[pageTableIndex] == 1)
                {
                    refPageTable[pageTableIndex] = 0;
                    pageTableIndex = (pageTableIndex + 1) % tableSize;
                }
                pageTable[pageTableIndex] = pageRequest;
                refPageTable[pageTableIndex] = 0;
                pageTableIndex = (pageTableIndex + 1) % tableSize;
            }
        }
        else
        { //if the item already exists in our main memory, we need to set its reference bit
            int k;
            for (k = 0; k < tableSize; k++)
            {
                if (pageRequest == pageTable[k])
                {
                    refPageTable[k] = 1;
                    break;
                }
            }
        }
    }
    printf("Hit rate = %f\n", (numRequest - numMisses) / (double)numRequest);
    free(input);
    free(pageTable);

    //Closing the files
    fclose(fp);
    fclose(wp);
    return 0;
}
