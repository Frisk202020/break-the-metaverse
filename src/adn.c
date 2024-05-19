#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "firewall.h"

/* Create a random DNA string of length N*/
char* string(int N){
    char* s = (char*)malloc(N*sizeof(char));
    for (int i = 0; i < N; i++){
        int r = rand()%4;
        if (r == 0){
            s[i] = 'A';
        }
        else if (r == 1){
            s[i] = 'C';
        }
        else if (r == 2){
            s[i] = 'T';
        }
        else{
            s[i] = 'G';
        }
    }

    return s;
}

/* Check if a character c belongs in the string s*/
bool belongs(char c, char* s, int N){
    for (int i = 0; i < N; i++){
        if (c == s[i]){
            return true;
        }
    }

    return false;
}

/* Convert characters into integers*/
int convert(char tenth, char unit){
    int n = 0;
    if (belongs(unit, "0123456789", 10)){ //check if the user prompted a two-digit number
        int d = 0;
        d += (tenth - 48);
        int u = 0;
        u += (unit - 48);

        n += 10*d;
        n += u;
        
        return n;
    }

    // if not, the unit is the first number, actually being tenth
    n += (tenth - 48);
    return n;
}

/* The software Flavie will use. Available prompts are listed on her manual*/
void software(){
    printf("DNA Analyzer - by Flavie Bit\n");

    srand(time(NULL));
    int N = rand()%10;
    N += 4;
    char* s = string(N);

    bool end = false;
    int current = 4;
    bool initialized = false;

    while(!end){
        char* prompt = (char*)malloc(100*sizeof(char));
        printf("> ");
        fgets(prompt, 100, stdin);

        if (!initialized){
            if (equal("initialize", prompt, 0, 10)){
                char* s0 = (char*)malloc(current*sizeof(char));
                for (int i = 0; i < current; i++){
                    s0[i] = s[i%N];
                }
                printf("%s\n", s0);
                free(s0);
                current++;    
                initialized = true;
            }
            else if (equal("end", prompt, 0, 3)){
                end = true;
            }
            else{
                printf("not initialized yet !\n");
            }
        }

        else{
            if (equal("initialize", prompt, 0, 10)){
                printf("already initialized\n");
            }
            else if (equal("next", prompt, 0, 4)){
                char* s0 = (char*)malloc(current*sizeof(char));
                for (int i = 0; i < current; i++){
                    s0[i] = s[i%N];
                }
                printf("%s (%d characters)\n", s0, current);
                free(s0);
                current++;
            }

            else if (equal("loop", prompt, 0, 4)){
                char d = prompt[5];
                char u = prompt[6];
                char more = prompt[7];
                if (belongs(more, "0123456789", 10)){
                    printf("loop n : n < 100 !!\n");
                }
                else if (belongs(d, "0123456789", 10)){
                    int n = convert(d, u);
                    if (n == N){
                        printf("Success !\n");
                        end = true;
                    }
                    else if (n < N){
                        printf("Failed to match the DNA. try a higher n input\n");
                    }
                    else{
                        printf("Failed to match the DNA. try a lower n input\n");
                    }
                }
                else{
                    printf("invalid second argument (argument n in prompt : loop n)\n");
                }
            }

            else if (equal("end", prompt, 0, 3)){
                end = true;
            }

            else{
                printf("invalid prompt\n");
            }
        }
        free(prompt);
    }
    free(s);
}

void main(){
    
    software();
}