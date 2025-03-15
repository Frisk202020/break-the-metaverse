#include "firewall.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void main(int argc, char** argv){
    if (argc > 1){
        if (strcmp(argv[1], "PIANO") == 0){
            printf("Dave hacking software -- seems like you've been trapped !\nBut if you're reading, you probably know me and thus the hack should be disabled, so go on and deactivate this software.\n\n");
            sleep(1);
            printf("Software deactivation -- 7 lines firewall to decipher. Prompt any key to start\n");
            char* prompt = (char*)malloc(100*sizeof(char));
            fgets(prompt, 100, stdin);
            free(prompt);
            if (firewall(7, "MAESTRO", 3, 50)){
                printf("\033[032mFile disabled\033[0m\n");
            }
            return;
        }
    }
    printf("\033[031mAccess Denied.\033[0m\n");
}