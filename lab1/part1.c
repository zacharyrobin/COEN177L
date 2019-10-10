#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/*
---- Part 1 ----
This simple shell program will launch a program called "HelloWorld.c" 
if the user enters in any string. This program will terminate if the user 
enters "exit". 

*/

int main()
{
    char in[256];
    int status;
    printf("PART1");
    while (true)
    {
        printf("enter exit to terminate or press any key to continue: ");
        scanf("%s", in);
        if (0 != strcmp(in, "exit"))
        {
            if (fork() != 0) // this progeam qwill fork and wait for the new child process to complete before returning.
            {
                waitpid(-1, &status, 0); // waiting for child to complete
            }
            else
            {
                execve("hello", NULL, NULL); // execute the program if the user enters in any string != exit
            }
        }
        else if (0 == strcmp(in, "exit"))  // if the user enters in a string == "exit" then the program will terminate 
        {
            printf("terminated \n");
            return;
        }
    }
}