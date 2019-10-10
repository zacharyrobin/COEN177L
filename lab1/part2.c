#include <unistd.h>
#include <stdio.h>

/*
---- Part 2 ----
This program creates exactly 6 child processes not including the initial program itself. 
*/


int main()
{
    int i;
  for(i=0;i<7;i++) // loop will run n times (n=7) 
    { 
        if(fork() != 0) 
        { 
            wait(NULL); // waiting until the child process is complete and then will terminate the child and return to the parent 
            break; // This program will never create more than two children processes
        } else {
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); // printing out the current PID and parent PID
        }
    } 
}