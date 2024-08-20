#include "firewall.h"

#include <stdio.h>
#include <unistd.h>

void main(){
    printf("Dave hacking software -- seems like you've been trapped !\nBut if you're reading, you probably know me and thus the hack should be disabled, so go on and deactivate this software.\n\n");
    sleep(1);
    printf("Software deactivation -- 4 lines firewall to decipher. Prompt any key to start\n");
    char* prompt = (char*)malloc(100*sizeof(char));
    fgets(prompt, 100, stdin);
    free(prompt);
    firewall(4, "BOOK", 2, 20);
}