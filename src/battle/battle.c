#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "battle.h"

/* Checks if the battle reaches the end (i-e one party goes down)*/
bool end(stats s){
    if (s.enemy.HP <= 0){
        printf("The enemy is defeated !\n");
        return true;
    }
    else{
        for (int i = 0; i < 5; i++){
            if (s.team[i].HP > 0){
                return false;
            }
        }
        printf("The team is defeated...\n");
        return true;
    }
}

/*
** Test for alive funtion **

void print_alive(stats s){
    crew Alive = alive(s);
    for (int i = 0; i < Alive.N; i++){
        printf("%s\n", Alive.team[i].name);
    }
}

*/

/* prints the health of all parties*/
stats reset_state(stats s){
    if (s.enemy.HP > s.enemy.maxHP){
        s.enemy.HP = s.enemy.maxHP;
    }

    if (s.turn == s.enemy.st.end){
        s.enemy.st.name = "normal";
    }
    for (int i = 0; i < 5; i++){
        if (s.turn == s.team[i].st.end){
            s.team[i].st.name = "normal";
            s.team[i].DEF = 0;
        }
    }

    return s;
}

/* 

*** Test : afficher les actions disponibles pour l'ennemi ***

void print_actions(stats s){
    for (int i = 0; i < s.enemy.NOA; i++){
        printf("%s ", s.enemy.actions[i].name);
    }
    printf("\n");
}

*/

void print_state(stats s){
    printf("\033[0;37m");
    printf("\n*** turn %d ***\n", s.turn);
    
    printf("\033[0;31m \nBoss : \033[0;35m ♥ %d \033[0;31m [%s] \033[0;0m\n\n", s.enemy.HP, s.enemy.st.name);

    for (int i = 0; i < 5; i++){
        if (s.team[i].HP < 0){
            s.team[i].HP = 0;
        }
        if (s.team[i].HP > s.team[i].maxHP){
            s.team[i].HP = s.team[i].maxHP;
        }
        if (s.team[i].HP == 0){
            printf("%s : DOWN\n", s.team[i].name);
        }
        else{
            printf("\033[0;36m %s : \033[0;35m ♥ %d \033[0;36m [%s] \033[0;0m\n", s.team[i].name, s.team[i].HP, s.team[i].st.name);
        }
    }
    printf("\n");
}

/* free all of what was allocated during this battle*/
void free_all(stats s){
    free(s.enemy.actions);

    for (int i = 0; i < 5; i++){
        free(s.team[i].actions);
    }
    free(s.team);
}

void main(){
    printf("Start of the battle against the dragon !\n");
    srand(time(NULL));
    stats s = dragon_initialize();
    assert_ennemy_stats(s.enemy);

    while (!end(s)){
        s = reset_state(s);
        print_state(s);
        char* prompt = (char*)malloc(100*sizeof(char));
        printf("> ");
        fgets(prompt, 100, stdin);

        if (equal("attack", prompt, 0, 6)){
            bool done = false;
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 7, 7+s.team[i].name_length)){
                    done = true;
                    if (s.team[i].HP <= 0){
                        printf("You can't attack with a K-O character\n");
                    }
                    else{
                        char d = prompt[8+s.team[i].name_length];
                        char u = prompt[9+s.team[i].name_length];
                        int dice = convert(d, u);
                        int att = attack(s.team[i], dice_range(s.team[i], dice));
                        s.enemy.HP -= att;
                    }
                }
            }

            if (equal(s.enemy.name, prompt, 7, 13)){
                done = true;
                s = enemy_attack(s);  
                s.turn++;             
            }
            
            if (!done){
                printf("Unreconized character\n");
            }
        }

        else if (equal("action", prompt, 0, 6)){
            bool done = false;
            bool found = false;
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 7, 7+s.team[i].name_length)){
                    done = true;
                    if (s.team[i].HP <= 0){
                        printf("You can't act with a K-O character\n");
                    }
                    else{
                        for (int j = 0; j < s.team[i].NOA; j++){
                            if (equal(s.team[i].actions[j].name, prompt, 8+s.team[i].name_length, 8+s.team[i].name_length+s.team[i].actions[j].name_length)){
                                found = true;
                                s = execute_action(s, s.team[i].actions[j], i, j);
                            }
                        }
                    }
                }
            }
            if (!done){
                printf("Unreconized character\n");
            }
            if (!found){
                printf("Unreconized action\n");
            }
        }

        else{
            printf("Unreconized prompt\n");
            s.enemy.HP = 0;
        }
        free(prompt);
    }
    free_all(s);
}