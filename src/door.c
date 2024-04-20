#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int strcmp(const char* s1, const char* s2);

bool equal(char* s, char* prompt, int d, int e){
    char* ans = (char*)malloc((e-d+1)*sizeof(char));
    ans[e-d] = '\0';
    for (int i = d; i < e; i++){
        ans[i-d] = prompt[i];
    }
    if (strcmp(s, ans) == 0){
        free(ans);
        return true;
    }
    free(ans);
    return false;
}

int main(){
    FILE *file = NULL;
    file = fopen("data.txt","r");
    char* state = (char*)malloc(100*sizeof(char));
    fscanf(file, "The door is currently : *%s*", state);
    if (equal("CLOSED", state, 0, 6)){
        file = fopen("data.txt","w");
        printf("State : CLOSED. Would you like to open it ? (Y/n)\n");
        char* c = (char*)malloc(sizeof(char));
        scanf("%c", c);
        if (*c != 'N' && *c != 'n'){
            fprintf(file, "The door is currently : *OPENED*\n");
        } 
        else{
            fprintf(file, "The door is currently : *CLOSED*\n");
        }
        free(c);
    }
    else{
        file = fopen("data.txt","w");
        printf("State : OPENED. Would you like to close it ? (Y/n)\n");
        char* c = (char*)malloc(sizeof(char));
        scanf("%c", c);
        if (*c != 'N' && *c != 'n'){
            fprintf(file, "The door is currently : *CLOSED*\n");
        } 
        else{
            fprintf(file, "The door is currently : *OPENED*\n");
        }
        free(c);
    }
    
}