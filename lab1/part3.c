#include <unistd.h>
#include <stdio.h>

int main()
{
    int i;
    int pid;
  for(i=0;i<14;i++) // loop will run n times (n=5) 
    { 
        if((pid = fork()) != 0) // if its a parent
        { 
            wait(NULL);
            break; // break
        } else {
            printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid());

        }
    } 
}
