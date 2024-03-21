#include <stdio.h>
#include "../include/AXelle.h"

void AXelle_terminal(){
    printf("AXelle@Home: ");
    char* paths[3] = {"data", "bin", "doc"};
    char* data = NULL
    char* bin[2] = {"how to crush"}
    char prompt[200];
    scanf("%99[^ \t\n]", prompt);
    for (int i = 0; i < 3; i++){
        if (strcmp(prompt, paths[i]) == 0){
            printf("hello to you");
        }
    }
    
}