#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

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
            if (fork() != 0)
            {
                waitpid(-1, &status, 0);
            }
            else
            {
                execve("hello", NULL, NULL);
            }
        }
        else if (0 == strcmp(in, "exit"))
        {
            printf("terminated \n");
            return;
        }
    }
}