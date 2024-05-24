/*
@Brief : Outputs the ammount of dammage an ennemy will endure
@Param : 
    - ch : the character who's attacking
    - dice :  the range of the dice (0: bad, 1: ok, 2: excellent, 3: perfect)
Ranges of the dices :
    - 4 faces : [1, 2, 3, 4] (most balanced, highest perfect probability)
    - 6 faces : [1, 2~3, 4~5, 6] (balanced)
    - 8 faces : [1, 2~3, 4~7, 8] (high-probability of great result)
    - 10 faces : [1, 2~7, 8~9, 10] (high-probability of poor result)
    - 12 faces  : [1~4, 5~8, 9~11, 12] (balanced)
    - 20 faces : [1~7, 8~15, 16~19, 20] (balanced)
    - 30 faces : [1, 2~15, 16~29, 30] (high-probability of mid-result)
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "battle.h"

/* Attributes a grade to a dice throw regarding the charcater*/
int dice_range(character ch, int result){
    int faces = ch.dice;
    if (faces == 4){
        return (result - 1);
    }
    else if (faces == 6){
        if (result == 1){
            return 0;
        }
        else if (result == 2 || result == 3){
            return 1;
        }
        else if (result == 6){
            return 3;
        }
        else{
            return 2;
        }
    }
    else if (faces == 8){
        if (result == 8){
            return 3;
        }
        else if (result == 1){
            return 0;
        }
        else if (result == 2 || result == 3){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if (faces == 10){
        if (result == 10){
            return 3;
        }
        else if (result == 1){
            return 0;
        }
        else if (result == 8 || result == 9){
            return 2;
        }
        else{
            return 1;
        }
    }
    else if (faces == 12){
        if (result == 12){
            return 3;
        }
        else if (result < 5){
            return 0;
        }
        else if (result > 4 && result < 9){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if (faces == 20){
        if (result == 20){
            return 3;
        }
        else if (result < 8){
            return 0;
        }
        else if (result < 16 && result > 7){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if (faces == 30){
        if (result == 30){
            return 3;
        }
        else if (result == 1){
            return 0;
        }
        else if (result > 1 && result < 16){
            return 1;
        }
        else{
            return 2;
        }
    }
}

/* Attributes an attack result based of the character and a dice throw*/
int attack(character ch, int dice){
    int pow = ch.POW;
    if (equal(ch.st.name, "focus success", 0, 13)){
        printf("\033[0;32m %s will doo massive damage !\n", ch.name);
        return 3*pow;
    }
    else if (dice == 0){
        return entropy(pow, 10, 10);
    }
    else if (dice == 1){
        return entropy(pow, 20, 30);
    }
    else if (dice == 2){
        return entropy(pow, 50, 40);
    }
    else{
        return pow;
    }
}

bool action_success(action act){
    bool* arr = (bool*)malloc(100*sizeof(bool));
    int count = 0;
    for (int i = 0; i < 100; i++){
        if (count < act.odd){
            arr[i] = true;
            count++;
        }
        else{
            arr[i] = false;
        }
    }
    bool pick = arr[rand()%100];
    free(arr);
    return pick;
}

stats special_act(action act, stats s){
    if (equal("stun", act.st.name, 0, 4)){
        s.enemy.st.name = "stun";
        s.enemy.st.end = s.turn + act.st.end;
        printf("\033[0;32m The enemy can't attack for the following turn \033[0;0m\n");
    }

    else if (equal("provoke", act.st.name, 0, 7)){
        s.enemy.st.name = "Derek";
        s.enemy.st.end = s.turn + act.st.end;
        printf("\033[0;32m The enemy will focus Derek for 2 turns \033[0;0m\n");
    }
    
    else if (equal("corrupt", act.st.name, 0, 7)){
        if (s.enemy.NOA < 4){
            printf("The enemy has already drank the potion\n");
            return s;
        }
        action* new_actions = (action*)malloc(3*sizeof(action));
        for (int i = 0; i < 3; i++){
            new_actions[i] = s.enemy.actions[i+1];
        }
        free(s.enemy.actions);
        s.enemy.actions = new_actions;
        s.enemy.actions[0].odd = 50;
        s.enemy.actions[1].odd = 45;
        s.enemy.actions[2].odd = 5;
        s.enemy.NOA -= 1;
        printf("The dragon can't breath fire anymore !\n");
    }

    else{
        printf("Unreconized state\n");
    }
    return s;
}

stats execute_action(stats s, action act, int ch_id, int act_id){
    if (act.type == 'g'){
        if (act.POW > 0){
            s.enemy.HP -= act.POW;
            if (equal(act.st.name, "danger", 0, 6)){
                int pick = rand()%100;
                s.team[ch_id].HP -= Int(act.POW * pick / 100.);
                printf("\033[0;31m %s hurts themselves from the action \033[0;0m\n", s.team[ch_id].name);
            }
        }
        
        if (act.heal > 0){
            if (equal("defense", act.st.name, 0, 7)){
                if (ch_id < 5){
                    s.team[ch_id].st.name = "defense";
                    s.team[ch_id].st.end = s.turn + act.st.end;
                    s.team[ch_id].DEF += act.heal;
                    printf("\033[0;32m %s has high defense for %d turns ! \033[0;0m\n", s.team[ch_id].name, act.st.end);
                }
                else{
                    for (int i = 0; i < 5; i++){
                        s.team[i].st.name = "defense";
                        s.team[i].st.end = s.turn + act.st.end;
                        s.team[i].DEF += act.heal;
                    }
                    printf("\033[0;32m The party has high defense for %d turns ! \033[0;0m\n", act.st.end);
                }
            }
        }

        else if (equal("clone", act.st.name, 0, 5)){
            s.team[ch_id].st.name = "clone";
            s.team[ch_id].st.end = s.turn + act.st.end;
            printf("\033[0;32m Clover creates 2 clones that stand for 3 turns \033[0;0m\n");
        }

        else if (!equal("normal", act.st.name, 0, 6) && !equal("defense", act.st.name, 0, 7) && !equal("danger", act.st.name, 0, 6)){    
            s = special_act(act, s);
        }
    }
    else if (act.type == 'l'){
        if (action_success(act)){
            printf("\033[0;32m Executing %s... \033[0;0m\n", act.name);

            if (act.POW > 0 && !equal(act.st.name, "boost", 0, 5)){
                s.enemy.HP -= act.POW;
            }

            else if (equal(act.st.name, "boost", 0, 5)){
                s.team[ch_id].POW += act.POW;
            }

            else if (equal("focus", act.st.name, 0, 5)){
                s.team[ch_id].st.name = "focus";
                s.team[ch_id].st.end = -1;
            }

            if (!equal("normal", act.st.name, 0, 6) && !equal(act.st.name, "boost", 0, 5)){    
                s = special_act(act, s);
            }
        }
        else{
            printf("\033[0;31m action failed ! \033[0;0m\n");
        }
    }
    else{
        char* prompt = (char*)malloc(100*sizeof(char));
        printf("Look at the battle book to see the action success condition\nIs action successful (y/N) ? ");
        fgets(prompt, 100, stdin);
        if (equal("y", prompt, 0, 1)){
            printf("\033[0;32m Success ! \033[0;0m\n");
            if (act.POW > 0){
                s.enemy.HP -= act.POW;
            }
            else if (!equal("normal", act.st.name, 0, 6)){    
                s = special_act(act, s);
            }
        }
        else{
            printf("\033[0;31m Fail... \033[0;0m\n");
        }
        free(prompt);
    }
    return s;
}

void assert_ennemy_stats(character ch){
    action* test = ch.actions;
    int sum = 0;
    for (int i = 0; i < ch.NOA; i++){
        sum += test[i].odd;
    }
    assert(sum == 100);
}

/* 
   ** Test for choose_enemy_action ** 

void test_enemy_choose(int* arr){
    int zero = 0;
    int one = 0;
    int two = 0;
    int three = 0;
    for (int i = 0; i < 100; i++){
        if (arr[i] == 0){
            zero++;
        }
        else if (arr[i] == 1){
            one++;
        }
        else if (arr[i] == 2){
            two++;
        }
        else {
            three++;
        }
    }
    printf("%d %d %d %d\n", zero, one, two, three);
}

*/

action choose_enemy_action(action* acts){
    int* arr = (int*)malloc(100*sizeof(int));
    int count = 0;
    int j = 0;
    for (int i = 0; i < 100; i++){
        if (j < acts[count].odd){
            arr[i] = count;
            j++;
        }
        else{
            j = 1;
            count++;
            arr[i] = count;
        }
    }
    int pick = arr[rand()%100];
    free(arr);
    return acts[pick];
}

stats enemy_attack(stats s){
    if (!equal(s.enemy.st.name, "stun", 0, 4)){
        assert_ennemy_stats(s.enemy);
        action Action = choose_enemy_action(s.enemy.actions);
        printf("The enemy attacks with %s !\n", Action.name);
        bool dodge = false;
        bool shield = false;

        if (Action.POW > 0){
            if (Action.aim == 'a'){
                for (int i = 0; i < 5; i++){
                    if (equal(s.team[i].st.name, "focus", 0, 5)){
                        printf("Focus failed\n");
                        s.team[i].st.name = "normal";
                    }
                    if (s.team[i].DEF == 100){
                        printf("\033[0;32m %s is protected\033[0;0m\n", s.team[i].name);
                    }
                    else if (equal("clone", s.team[i].st.name, 0, 5)){
                        char* picks[3] = {"left", "middle", "right"};
                        char* pick = picks[rand()%3];
                        printf("The enemy picks the %s clone : is Clover protected ? (y/N) ", pick);
                        char* ans = (char*)malloc(100*sizeof(char));
                        fgets(ans, 100, stdin);
                        shield = true;
                        if (ans[0] != 'y'){
                            shield = false;
                            s.team[i].HP -= Int(0.01*(100 - s.team[i].DEF)*entropy(Action.POW, 100, 40));
                        }
                        free(ans);
                    }
                    else{
                        s.team[i].HP -= Int(0.01*(100 - s.team[i].DEF)*entropy(Action.POW, 100, 40));
                    }
                }
            }

            else{
                character* target = &(s.team[0]);
                crew Alive;

                if (equal("normal", s.enemy.st.name, 0, 6)){
                    Alive = alive(s);
                    int targetID = rand()%Alive.N;
                    target = (Alive.team[targetID]);
                    if (target->DEF == 100){
                        printf("The target is %s, but they're protected !\n", target->name);
                    }
        
                    else if (equal(target->st.name, "focus", 0, 5)){
                        printf("Focus failed\n");
                        target->st.name = "normal";
                    }
                    else{
                        printf("The target is %s !\n", target->name);
                    }
                }
                else{
                    for (int i = 0; i < 5; i++){
                        if (equal(s.team[i].name, s.enemy.st.name, 0, s.team[i].name_length)){
                            target = (&(s.team[i]));
                            if (target->DEF == 100){
                                printf("\033[0;32m The enemy focuses %s, but they're protected !\033[0;0m\n", target->name);
                                shield = true;
                            }
                            else{
                                printf("The enemy focuses %s !\n", target->name);
                            }
                        }  
                    }
                }

                if (Action.superguard){
                    char* prompt = (char*)malloc(100*sizeof(char));
                    printf("Attack dodged (y/N)? ");
                    fgets(prompt, 100, stdin);
                    if (equal("y", prompt, 0, 1)){
                        dodge = true;
                    }
                    free(prompt);
                }
                if (!dodge){
                    if (!shield){
                        if (equal("clone", target->st.name, 0, 5)){
                            char* picks[3] = {"left", "middle", "right"};
                            char* pick = picks[rand()%3];
                            printf("The enemy picks the %s clone : is Clover protected ? (y/N) ", pick);
                            char* ans = (char*)malloc(100*sizeof(char));
                            fgets(ans, 100, stdin);
                            shield = true;
                            if (ans[0] != 'y'){
                                shield = false;
                                target->HP -= Int(0.01*(100 - target->DEF)*entropy(Action.POW, 100, 40));
                            }
                            free(ans);
                        }
                        else{
                            target->HP -= Int(0.01*(100 - target->DEF)*entropy(Action.POW, 80, 30));
                        }
                    }
                }
                if (equal("normal", s.enemy.st.name, 0, 6)){
                    free(Alive.team);
                }
            }
        } 

        if (Action.heal > 0 && !dodge && !shield){
            int recover = entropy(Action.heal, 100, 100);
            printf("\033[0;35m The enemy recovers %d hearts ! \033[0;0m\n", recover);
            s.enemy.HP += recover;
        }

        for (int i = 0; i < 5; i++){
            if (equal(s.team[i].st.name, "focus", 0, 5)){
                s.team[i].st.name = "focus success";
                s.team[i].st.end = s.turn + 2;
            }
        }

        return s;
    }
    else{
        printf("\033[0;31m The enemy recovers \033[0;0m\n");
    }
}

crew alive(stats s){
    int n = 0;
    bool* alive = (bool*)malloc(5*sizeof(bool));
    for (int i = 0; i < 5; i++){
        if (s.team[i].HP > 0){
            alive[i] = true;
            n++;
        }
        else{
            alive[i] = false;
        }
    }
    crew ans = {
        .N = n,
        .team = malloc(n*sizeof(character*)),
    };
    int count = 0;
    for (int i = 0; i < 5; i++){
        if (alive[i]){
            ans.team[count] = &(s.team[i]);
            count++;
        }
    }
    free(alive);
    return ans;
}

/* 

***Code pour tester dice_range***

void main(int argc, char *argv[]){
    char* f = argv[1];
    char* r = argv[2];

    int faces = convert(f[0], f[1]);
    int result = convert(r[0], r[1]);
    printf("%d\n", dice_range(faces, result));
}

*/
