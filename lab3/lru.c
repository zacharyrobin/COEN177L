
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
    int pageRequest, pageTableIndex = 0, numRequest = 0, numMisses = 0;
    int *pageTable = (int *)malloc(sizeof(int) * tableSize);

    FILE *fp; //input
    char buff[255];
    fp = fopen("accesses.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file!");
        return 1;
    }

    FILE *wp; //file we are writing to as output
    wp = fopen("lruOutput.txt", "w");

    //need to change this to the file that he gives us instead of null
    // char *input = NULL;

    size_t inputAllocated = 0;
    size_t bytesRead;
    char str[255];  //buffer read

    while ((fgets(str, 255, fp)) != NULL)
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
            fprintf(fp, "Page %d caused a page fault.\n", pageRequest);
            fprintf(wp, "Page %d caused a page fault.\n", pageRequest);
            numMisses++; //increment our number of misses if we have a page fault, signifying that it's not in our main memory
            if (pageTableIndex < tableSize)
            { //check if we can hold more pages
                int o;
                for (o = pageTableIndex; o > 0; o--)
                {
                    pageTable[o] = pageTable[o - 1];
                }
                pageTableIndex++;
                pageTable[0] = pageRequest; //insert at the head of the array
            }
            else
            { //if array is full, then we need to perform FIFO, which means to remove the first page from the queue and queue both and insert the current page
                int p;
                for (p = tableSize - 1; p > 0; p--)
                {
                    pageTable[p] = pageTable[p - 1];
                }
                pageTable[0] = pageRequest; //make out pageRequest the newest item in the array
            }
        }
        else
        {
            int j;
            int i;
            for (i = 0; i < tableSize; i++)
            {
                if (pageTable[i] == pageRequest)
                { //if the item we are trying to add already exists in the array, we want to shift everything up until that particular spot
                    j = i;
                    break;
                }
            }
            int k;
            for (k = j; k > 0; k--)
            {
                pageTable[k] = pageTable[k - 1]; //shift everything up by 1 spot, from the point of the least recently used e
            }
            pageTable[0] = pageRequest; //make out pageRequest the newest item in the array
        }
    }
        printf("Hit rate = %f\n", (numRequest - numMisses) / (double)numRequest);
        free(pageTable);

        //Closing the files
        fclose(fp);
        fclose(wp);
        return 0;
    }
