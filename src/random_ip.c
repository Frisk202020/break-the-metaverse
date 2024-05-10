#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
    srand(time(NULL));
    char* ip = (char*)malloc(15*sizeof(char));
    ip[0] = '1';
    for (int i = 0; i < 4; i++){
        if (i != 0){
            ip[3*i + (i-1)] = '.';
        }
        for (int j = 0; j < 3; j++){
            if (i+j != 0){
                ip[4*i + j] = '0'+rand()%10;
            }
        }
    }
    printf("%s\n", ip);
    free(ip);
}