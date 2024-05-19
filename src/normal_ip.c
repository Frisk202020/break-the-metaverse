#include <stdio.h>
#include <stdlib.h>

#include "translate.h"

/* Translation from UNDERDOG numbers to normal numbers*/
void main(int argc, char* argv[]){
    char* input = argv[1];
    char* ans = (char*)malloc(15*sizeof(char));
    for (int i = 0; i < 15; i++){
        if (input[i] == '.'){
            ans[i] = '.';
        }
        else{
            ans[i] = underdog_to_normal(input[i]);
        }
    }
    printf("%s\n", ans);
    free(ans);
}