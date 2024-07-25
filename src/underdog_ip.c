#include <stdio.h>
#include <stdlib.h>

#include "translate.h"

void main(int argc, char* argv[]){
    if (argv[1] == NULL){
        printf("please prompt a valid ip\n");
        return;
    }

    int mode = 0;
    printf("\033[0;31mIf the IP is UNDERDOG, prompt 'y'. If the IP is normal, prompt any key : \033[0;0m");
    char* prompt = (char*)malloc(100*sizeof(char));
    fgets(prompt, 100, stdin);
    if (prompt[0] == 'y'){
        mode = 1;
    }
    free(prompt);


    char* input = argv[1];
    char* ans = (char*)malloc(15*sizeof(char));
    for (int i = 0; i < 15; i++){
        if (input[i] == '.'){
            ans[i] = '.';
        }
        else{
            if (mode == 0){
                ans[i] = normal_to_underdog(input[i]);
            }
            else{
                ans[i] = underdog_to_normal(input[i]);
            }
        }
    }
    printf("%s\n", ans);
    free(ans);
}