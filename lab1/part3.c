#include <unistd.h>
#include <stdio.h>

int main()
{
    int i;
  for(i=0;i<4;i++) // loop will run n times (n=7) 
    { 
        if(fork() == 1) // if its a parent
        { 
            fork();
            wait(NULL);
            break;
        }
        else {
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid());
        }
    } 
}