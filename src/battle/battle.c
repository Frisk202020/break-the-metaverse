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
void print_state(stats* s_p){
    stats s = *s_p;
    if (s.enemy.HP > s.enemy.maxHP){
        s_p->enemy.HP = s.enemy.maxHP;
    }
    s = *s_p;
    printf("\nBoss : ♥ %d\n\n", s.enemy.HP);

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
            printf("%s : ♥ %d\n", s.team[i].name, s.team[i].HP);
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
    stats s = dragon_initialize();
    assert_ennemy_stats(s.enemy);

    while (!end(s)){
        print_state(&(s));
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
                enemy_attack(&(s));               
            }
            
            if (!done){
                printf("Unreconized character\n");
            }
        }

        else if (equal("action", prompt, 0, 6)){
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 7, 7+s.team[i].name_length)){
                    if (s.team[i].HP <= 0){
                        printf("You can't act with a K-O character\n");
                    }
                    else{
                        for (int j = 0; j < s.team[i].NOA; j++){
                            if (equal(s.team[i].actions[j].name, prompt, 8+s.team[i].name_length, 8+s.team[i].name_length+s.team[i].actions[j].name_length)){
                                execute_action(&(s), s.team[i].actions[j], i, j);
                            }
                        }
                    }
                }
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