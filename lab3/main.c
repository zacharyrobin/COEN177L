#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
        printf("You have entered %d", argc, "\n"); 
  int i;
    for ( i = 0; i < argc; ++i) 
        printf( "%c", argv[i],"\n"); 


    return 0;
}