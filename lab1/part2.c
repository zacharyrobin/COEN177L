#include <unistd.h>
#include <stdio.h>

int main()
{
    int i;
  for(i=0;i<7;i++) // loop will run n times (n=7) 
    { 
        if(fork() != 0) 
        { 
            wait(NULL);
            break;
        } else {
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); 
        }
    } 
}