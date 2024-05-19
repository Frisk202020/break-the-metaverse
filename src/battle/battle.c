#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "battle.h"

/* Checks if the battle reaches the end (i-e one party goes down)*/
bool end(stats s){
    if (s.enemy.HP <= 0){
        return true;
    }
    else{
        for (int i = 0; i < 5; i++){
            if (s.team[i].HP > 0){
                return false;
            }
        }
        return true;
    }
}

/* prints the health of all parties*/
void print_state(stats s){
    printf("\n** Enemy : HP = %d **\n\n", s.enemy.HP);
    for (int i = 0; i < 5; i++){
        printf("♥♥ %s : HP = %d ♥♥\n", s.team[i].name, s.team[i].HP);
    }
    printf("\n");
}

/* free all of what was allocated during this battle*/
void free_all(stats s){
    free(s.team);
}

void main(){
    printf("Start of the battle against the dragon !\n");
    stats s = dragon_initialize();

    while (!end(s)){
        print_state(s);
        char* prompt = (char*)malloc(100*sizeof(char));
        printf("> ");
        fgets(prompt, 100, stdin);

        if (equal("attack", prompt, 0, 6)){
            if (equal("Derek", prompt, 7, 12)){    
                char d = prompt[13];
                char u = prompt[14];
                int dice = convert(d, u);
                int att = attack(s.team[0], dice_range(s.team[0], dice));
                s.enemy.HP -= att;
            }

            else if (equal("Flavie", prompt, 7, 13)){
                char d = prompt[14];
                char u = prompt[15];
                int dice = convert(d, u);
                int att = attack(s.team[1], dice_range(s.team[1], dice));
                s.enemy.HP -= att;
            }

            else if (equal("Haloise", prompt, 7, 14)){
                char d = prompt[15];
                char u = prompt[16];
                int dice = convert(d, u);
                int att = attack(s.team[2], dice_range(s.team[2], dice));
                s.enemy.HP -= att;
            }

            else if (equal("Xhara", prompt, 7, 12)){
                char d = prompt[13];
                char u = prompt[14];
                int dice = convert(d, u);
                int att = attack(s.team[3], dice_range(s.team[3], dice));
                s.enemy.HP -= att;
            }

            else if (equal("Clover", prompt, 7, 13)){
                char d = prompt[14];
                char u = prompt[15];
                int dice = convert(d, u);
                int att = attack(s.team[4], dice_range(s.team[4], dice));
                s.enemy.HP -= att;
            }
            
            else{
                printf("Unreconized character\n");
            }
        }
        else{
            printf("issue\n");
            s.enemy.HP = 0;
        }
        free(prompt);
    }
    free_all(s);
}