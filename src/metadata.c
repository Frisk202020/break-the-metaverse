#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* simulates a data file for entering a metaverse*/
void main(){

    srand(time(NULL));
    while (1 == 1){
        int n = rand()%2;
        if (n == 0){
            printf("0"); 
        }
        else{
            printf("1");
        }
    }      
}
