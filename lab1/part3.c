#include <unistd.h>
#include <stdio.h>
#include <string.h>


/*
---- Part 3 ----
This program when launched will create a total of fourteen child processes to run.
However, this program will not create less than two children or more than three 
children processes. This program runs as a binary tree with each child creating two
 more children for 4 levels until the desired 14 children is reacehd.

*/

int main(void)
{
    int N = 2; // number of children to be created  
    int pid = 0;
    int i = 0;
    int L = 1;  // Level  
    int status;
    printf("Main process PID %d\n", getpid());
    for (i = 0; i < N; i++)
    {
        int child = fork();
        // when fork is a child, the loop parameters are reset resulting in two new processes
        if (child == 0)
        {
            printf("PID %d | child of PID %d\n", getpid(), getppid());
            if (i == 1)
            {
                N = 2;
            }
            i = -1;
            L++; // incrementing the level 
        }
        else if (child > 0)
        {
            pid = 1;
            waitpid(-1, &status, 0); // waiting for the child processes to complete before terminating 
        }
        if (L >= 4) // we will only go down 4 levels to get to the desired 14 children in a binary tree 
        {
            break; // if we do not break this could result in a memory leak 
        }
    }
}