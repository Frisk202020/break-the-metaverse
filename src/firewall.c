#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "firewall.h"

void print_matrix(char** arr, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(char** arr, int s){
    for (int i = 0; i < s; i++){
        free(arr[i]);
    }
    free(arr);
}

bool done(state* s, int lines){
    for (int i = 0; i < lines; i++){
        if (!s[i].checked){
            return false;
        }
    }
    return true;
}

char toString(int n){
    char* ans = "0123456789";
    int num[10] = {0,1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < 10; i++){
        if (n == num[i]){
            return ans[i];
        }
    }
    return '&';
}

/* Checks if strings s and prompt[e : d] are equal. */
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

/* analyze command of the software : reveals a character of the firewall*/
void analyze(char** wall, int lines, char* sol, int* left, state* s){
    if (*left == 0){
        printf("\033[0;31mYou already analyzed every line of the firewall !\033[0;0m\n");
        return;
    }
    if (!done(s, lines)){
        int* pos = (int*)malloc(*left*sizeof(int));
        int ind = 0;
        for (int i = 0; i < lines; i++){
            if (!s[i].checked){
                pos[ind] = i;
                ind++;
            }
        }

        int chosen = pos[rand()%*left];
        s[chosen].checked = true;
        *left -= 1;
    
        for (int i = 0; i < lines; i++){
            for (int j = 0; j < lines; j++){
                if (s[i].checked && !s[i].done){
                    if (j == s[i].position){
                        wall[i][j] = s[i].value;
                    }
                    else{
                        wall[i][j] = toString(rand()%10);
                    }
                }
                else{
                    wall[i][j] = 'A';
                    int incr = rand()%25;
                    wall[i][j] += incr;
                }
            }
        }
        s[chosen].done = true;
        free(pos);
        print_matrix(wall, lines);
    }
    else{
        print_matrix(wall, lines);
    }
}

/* The firewall destroyer software*/
bool firewall(int lines, char* sol, float cooldown, int timer){
    /**
    * @param lines : lines of the firewall 
    */

    //initialisation
    char** wall = (char**)malloc(lines*sizeof(char*));
    for (int i = 0; i < lines; i++){
        wall[i] = malloc(lines*sizeof(char)); 
    }

    srand(time(NULL));
    int* left = (int*)malloc(sizeof(int));
    *left = lines;
    
    state* s = (state*)malloc(lines*sizeof(state));
    for (int i = 0; i < lines; i++){
        s[i].checked = false;
        s[i].done = false;
        s[i].value = sol[i]; 
        s[i].position = rand()%lines; 
    }

    bool end = false;
    int ind = 0;
    time_t start = time(NULL);
    while (!end){
        time_t current = time(NULL) - start;
        if (timer > 0){
            if (current < timer){
                printf("\033[0;31mtime remaining : %ld seconds\033[0;0m\n", (timer - current));
            }
            else{
                printf("\033[0;31mFirewall deactivation failed.\033[0;0m\n");
                free(left);
                free(s);
                return false;
            }
        }
        char* prompt = (char*)malloc(100*sizeof(char));
        printf("> ");
        fgets(prompt, 100, stdin);
        current = time(NULL) - start;
        if (timer > 0){
            if (current >= timer){
                printf("\033[0;31mFirewall deactivation failed.\033[0;0m\n");
                free(left);
                free(s);
                free(prompt);
                return false;
            }
        }
        //décodage
        if (equal("analyze", prompt, 0, 7)){
            sleep(cooldown);
            printf("\n");
            analyze(wall, lines, sol, left, s);
            printf("\n");
        }

        else if (equal("solve", prompt, 0, 5)){
            if (equal(sol, prompt, 6, 6+lines)){
                sleep(2);
                printf("firewall disabled !\n");
                end = true;
                free(left);
                free(s);
            }
            else{
                printf("incorrect solution\n");
            }
        }
        else{
            printf("Unrecognized\n");
        }

        free(prompt);
    }
    free_matrix(wall, lines);
    return true;
}
