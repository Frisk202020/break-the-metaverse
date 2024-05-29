#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "battle.h"

/* Checks if the battle reaches the end (i-e one party goes down)*/
bool end(stats s){
    if (s.enemy.HP <= 0){
        printf("\033[0;32m The enemy is defeated !\033[0;32m\n");
        return true;
    }
    else{
        if (equal("Dragon", s.enemy.name, 0, 6)){
            for (int i = 0; i < 5; i++){
                if (s.team[i].HP > 0){
                    return false;
                }
            }
            printf("\033[0;31m The team is defeated...\033[0;31m\n");
            return true;
        }
        else{
            for (int i = 0; i < 5; i++){
                if (s.team[i].HP <= 0){
                    print_state(s);
                    printf("\033[0;31m A character didn't pass the test...\033[0;31m\n");
                    return true;
                }
            }
        }
    }
}

state affect_state(char* retrieve, int end){
    state st;
    st.end = end;
    if (equal(retrieve, "normal", 0, 6)){
        st.name = "normal";
    }
    else if (equal(retrieve, "defense", 0, 7)){
        st.name = "defense";
    }
    else if (equal(retrieve, "focus", 0, 5)){
        st.name = "focus";
    }
    else if (equal(retrieve, "stun", 0, 4)){
        st.name = "stun";
    }
    else if (equal(retrieve, "Derek", 0, 5)){
        st.name = "Derek";
    }
    else if (equal(retrieve, "danger", 0, 6)){
        st.name = "danger";
    }
    else {
        st.name = "?";
        printf("%c%c%c", retrieve[0], retrieve[1], retrieve[2]);
    }

    return st;
}

// restore the state of the battle if the software crashed
stats restore_state(stats s){
    FILE* file = fopen("src/battle/data/state.txt", "r");
    assert(file != NULL);
    char* battle = (char*)malloc(100*sizeof(char));
    fscanf(file, "%s\n", battle);
    if (equal(battle, "Dragon", 0, 6)){
        s = dragon_initialize();
    }
    else if (equal(battle, "Sensei", 0, 6)){
        s = sensei_initialize();
    }
    free(battle);

    for (int i = 0; i < 5; i++){
        character ch = s.team[i];
        char* retrieve = (char*)malloc(100*sizeof(char));
        int* end = (int*)malloc(sizeof(int));
        fscanf(file, "%d %d %d %s %d\n", &(ch.HP), &(ch.POW), &(ch.DEF), retrieve, end);
        ch.st = affect_state(retrieve, *end);
        s.team[i] = ch;
        free(retrieve);
        free(end);
    }
    character ch = s.enemy;
    char* retrieve = (char*)malloc(100*sizeof(char));
    int end;
    fscanf(file, "%d %s %d\n", &(ch.HP), retrieve, &(end));
    ch.st = affect_state(retrieve, end);
    s.enemy = ch; 
    fscanf(file, "%d\n", &(s.turn));
    free(retrieve);
    fclose(file);
    return s;
}

// write the current state of the battle for every action
void write_state(stats s){
    FILE* file = fopen("src/battle/data/state.txt", "w");
    assert(file != NULL);
    fprintf(file, "%s\n", s.enemy.name);
    for (int i = 0; i < 5; i++){
        character ch = s.team[i];
        fprintf(file, "%d %d %d %s %d\n", ch.HP, ch.POW, ch.DEF, ch.st.name, ch.st.end);
    }
    character ch = s.enemy;
    fprintf(file, "%d %s %d\n%d\n", ch.HP, ch.st.name, ch.st.end, s.turn);
    fclose(file);
}

/* removes a state if the turn is right*/
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
void life_bar(character ch){
    int N = 20*ch.HP / ch.maxHP;
    printf("\033[0;32m");
    for (int i = 0; i < N; i++){
        printf("|");
    }
    printf("\033[0;31m");
    for (int i = N; i < 20; i++){
        printf("|");
    }
}

void print_state(stats s){
    if (equal(s.enemy.name, "Dragon", 0, 6)){
        printf("\033[0;37m");
        printf("\n*** turn %d ***\n", s.turn);
        
        printf("\033[0;31m \nBoss : \033[0;35m ♥ %d  ", s.enemy.HP); 
        life_bar(s.enemy);
        printf("\033[0;31m [%s] \033[0;0m\n\n", s.enemy.st.name);

        for (int i = 0; i < 5; i++){
            if (s.team[i].HP < 0){
                s.team[i].HP = 0;
            }
            if (s.team[i].HP > s.team[i].maxHP){
                s.team[i].HP = s.team[i].maxHP;
            }
            if (s.team[i].HP == 0){
                printf("\033[0;34m %s : DOWN \033[0;0m\n", s.team[i].name);
            }
            else{
                printf("\033[0;36m %s : \033[0;35m ♥ %d  ", s.team[i].name, s.team[i].HP);
                life_bar(s.team[i]);
                printf("\033[0;36m [%s] \033[0;0m\n", s.team[i].st.name);
            }
        }
        printf("\n");
    }
    else if (equal(s.enemy.name, "Sensei", 0, 6)){
        printf("\033[0;37m");
        printf("\n*** turn %d ***\n", s.turn);
        int gardes[5] = {18, 8, 12, 16, 10};
        char* belts[5] = {"\033[0;30m", "\033[0;32m", "\033[0;34m", "\033[0;33m", "\033[0;36m"};
        
        printf("\033[0;31m \nBoss : \033[0;35m ♥ %d  ", s.enemy.HP); 
        life_bar(s.enemy);
        printf("\033[0;31m [%s] \033[0;0m\n\n", s.enemy.st.name);

        for (int i = 0; i < 5; i++){
            if (s.team[i].HP < 0){
                s.team[i].HP = 0;
            }
            if (s.team[i].HP > s.team[i].maxHP){
                s.team[i].HP = s.team[i].maxHP;
            }
            if (s.team[i].HP == 0){
                printf("%s ", belts[i]);
                printf("%s : RE-TAKE EXAM \033[0;0m\n", s.team[i].name);
            }
            else{
                float grade = gardes[i] + s.team[i].HP/10.;
                printf("%s ", belts[i]);
                printf("%s : \033[0;35m Grade : %0.2f/20  ", s.team[i].name, grade);
                life_bar(s.team[i]);
                printf("%s ", belts[i]);
                printf("[%s] [%s]\033[0;0m\n", s.team[i].st.name, s.team[i].smell.name);
            }
        }
        printf("\n");
    }
}

/* free all of what was allocated during this battle*/
void free_all(stats s){
    free(s.enemy.actions);

    for (int i = 0; i < 5; i++){
        free(s.team[i].actions);
    }
    free(s.team);
}

void main(int argc, char *argv[]){
    srand(time(NULL));
    stats s;

    if (argc > 1){
        if (equal(argv[1], "restore", 0, 7)){
            printf("Restoring state...\n");
            s = restore_state(s);
        }
        else if (equal(argv[1], "Dragon", 0, 6)){
            printf("Start of the battle against the dragon !\n");
            s = dragon_initialize();
        }
        else if (equal(argv[1], "Sensei", 0, 6)){
            printf("Start of the battle against the sensei !\n");
            s = sensei_initialize();
        }
        else{
            printf("Unknown\n");
            return;
        }
    }

    else{
        printf("Please input which battle to launch !\n");
        return;
    }

    assert_ennemy_stats(s.enemy);
    bool the_end = false;
    while (!end(s) || the_end){
        s = reset_state(s);
        print_state(s);
        write_state(s);        

        char* prompt = (char*)malloc(100*sizeof(char));
        printf("> ");
        fgets(prompt, 100, stdin);

        if (equal("attack", prompt, 0, 6)){
            bool done = false;
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 7, 7+s.team[i].name_length)){
                    done = true;
                    if (s.team[i].HP <= 0){
                        printf("\033[0;31m You can't attack with a K-O character \033[0;0m\n");
                    }
                    else{
                        if (equal(s.enemy.name, "Dragon", 0, 6)){
                            char d = prompt[8+s.team[i].name_length];
                            char u = prompt[9+s.team[i].name_length];
                            int dice = convert(d, u);
                            int att = attack(s.team[i], dice_range(s.team[i], dice));
                            s.enemy.HP -= att;
                        }
                        else if (equal(s.enemy.name, "Sensei", 0, 6)){
                            char* prompt = (char*)malloc(100*sizeof(char));
                            printf("Did the player beat you ? (y/N) ");
                            fgets(prompt, 100, stdin);
                            if (prompt[0] == 'y'){
                                if (equal(s.team[i].smell.name, "lila", 0, 4)){
                                    s.enemy.HP -= 2*s.team[i].POW;
                                }
                                else if (equal(s.team[i].smell.name, "rotten egg", 0, 10)){
                                    printf("The attack failed because of the horrible smell");
                                }
                                else{
                                    s.enemy.HP -= s.team[i].POW;
                                }
                            }
                            else{
                                printf("\033[0;31m attack failed...\033[0;0m");
                            }
                            free(prompt);
                        }
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
                        printf("\033[0;31m You can't act with a K-O character \033[0;0m\n");
                    }
                    else if (equal("protect", prompt, 8+s.team[i].name_length, 15+s.team[i].name_length)){
                        for (int j = 0; j < 5; j++){
                            if (equal(s.team[j].name, prompt, 16+s.team[i].name_length, 16+s.team[i].name_length+s.team[j].name_length)){
                                if (equal("vulnerable", s.team[j].st.name, 0, 10)){
                                    printf("can't protect the character because they're already protecting someone");
                                }
                                else{
                                    s.team[j].st.name = s.team[i].name;
                                    s.team[j].st.end = s.turn + 1;
                                    s.team[i].st.name = "vulnerable";
                                    s.team[i].DEF = -100;
                                    s.team[i].st.end = s.turn + 1;
                                }
                            }
                        }
                    }
                    else{
                        for (int j = 0; j < s.team[i].NOA; j++){
                            if (equal(s.team[i].actions[j].name, prompt, 8+s.team[i].name_length, 8+s.team[i].name_length+s.team[i].actions[j].name_length)){
                                found = true;
                                if (s.team[i].actions[j].aim == 'i'){
                                    s = execute_action(s, s.team[i].actions[j], i, j);
                                }
                                else{
                                    s = execute_action(s, s.team[i].actions[j], 5, j);
                                }
                                if (s.team[i].actions[j].type == 'g'){
                                    s.team[i].actions[j].type = 'l';
                                    s.team[i].actions[j].odd = 0;
                                }
                            }
                        }
                        if (!found){
                            printf("Unreconized action\n");
                        }
                    }
                }
            }
            if (!done){
                printf("Unreconized character\n");
            }
        }
        else if (equal("exit", prompt, 0, 4)){
            free(prompt);
            free_all(s);
            return;
        }
        else{
            printf("Unreconized prompt\n");
        }
        free(prompt);
    }
    free_all(s);
}