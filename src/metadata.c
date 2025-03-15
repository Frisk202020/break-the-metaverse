#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

bool equal(char* s, char* prompt, int d, int e){
    char* ans = (char*)malloc((e-d+1)*sizeof(char));
    ans[e-d] = '\0';
    for (int i = d; i < e; i++){
        ans[i-d] = prompt[i];
    }
    //printf("%s %s\n", ans, s);
    if (strcmp(s, ans) == 0){
        free(ans);
        return true;
    }
    free(ans);
    return false;
}

void loop(){
    srand(time(NULL));
    printf("\033[0;32m");
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

/* simulates a data file for entering a metaverse*/
void main(int argc, char *argv[]){
    // Should be changed for each metaverse.
    char* key = NULL;
    int key_length = 0;

    if (key == NULL){
        loop();
    }
    if (argc > 1){
        printf("%d\n", argc);
        if (equal(key, argv[1], 0, key_length)){
            loop();
        }
    }
    printf("\033[0;31mAccess Denied !\033[0;0m\n");      
}
