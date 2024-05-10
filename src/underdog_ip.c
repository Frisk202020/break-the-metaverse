#include <stdio.h>
#include <stdlib.h>

#include "translate.h"

void main(int argc, char* argv[]){
    if (argv[1] == NULL){
        printf("please prompt a valid ip\n");
        return;
    }
    char* input = argv[1];
    char* ans = (char*)malloc(15*sizeof(char));
    for (int i = 0; i < 15; i++){
        if (input[i] == '.'){
            ans[i] = '.';
        }
        else{
            ans[i] = normal_to_underdog(input[i]);
        }
    }
    printf("%s\n", ans);
    free(ans);
}