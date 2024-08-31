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
    character target;
    int ID;
    if (s.nb_other == 0){
        target = s.enemy;
        ID = -1;
    }
    else{
        char* prompt = (char*)malloc(100*sizeof(char));
        printf("Who is the target of the action ? ");
        bool done = false;
        fgets(prompt, 100, stdin);
        if (equal(s.enemy.name, prompt, 0, s.enemy.name_length)){
            target = s.enemy;
            ID = -1;
            done = true;
        }
        else{
            for (int i = 0; i < s.nb_other; i++){
                if (equal(s.other[i].name, prompt, 0, s.other[i].name_length)){
                    target = s.other[i];
                    ID = i;
                    done = true;
                }
            }
        }
        if (!done){
            printf("Target not found !\n");
            return s;
        }
    }
    if (equal("stun", act.st.name, 0, 4)){
        target.st.name = "stun";
        target.st.end = s.turn + act.st.end;
        target.HP -= act.POW;
        printf("\033[0;32m The enemy can't attack for the following turn \033[0;0m\n");
    }

    else if (equal("provoke", act.st.name, 0, 7)){
        target.st.name = "Derek";
        target.st.end = s.turn + act.st.end;
        printf("\033[0;32m The enemy will focus Derek for 2 turns \033[0;0m\n");
    }
    
    else if (equal("corrupt", act.st.name, 0, 7)){
        if (target.NOA < 4){
            printf("The enemy has already drank the potion\n");
            return s;
        }
        action* new_actions = (action*)malloc(3*sizeof(action));
        for (int i = 0; i < 3; i++){
            new_actions[i] = target.actions[i+1];
        }
        free(target.actions);
        target.actions = new_actions;
        target.actions[0].odd = 50;
        target.actions[1].odd = 45;
        target.actions[2].odd = 5;
        target.NOA -= 1;
        printf("The dragon can't breath fire anymore !\n");
    }

    else if (equal("magic", act.name, 0, 6)){
        char* elements[5] = {"fire", "ice", "water", "light", "vegetal"};
        int arr[5] = {4, 3, 5, 5, 7};
        int i = 0;
        while (!equal(elements[i], act.st.name, 0, arr[i])){
            i++;
        }

        if (s.orb[0] < 0){
            s.orb[0] = i;
        }
        else if (s.orb[1] < 0){
            s.orb[1] = i;
        }
        else{
            printf("The orb is filled for this turn !\n");
        }
    }

    else{
        printf("Unreconized state\n");
    }
    
    if (ID == -1){
        s.enemy = target;
    }
    else{
        s.other[ID] = target;
    }
    return s;
}

stats action_when_many_enemies(stats s, action act){
    char* prompt = (char*)malloc(100*sizeof(char));
    printf("Who is the target of the action ? ");
    bool done = false;
    fgets(prompt, 100, stdin);
    if (equal(s.enemy.name, prompt, 0, s.enemy.name_length)){
        s.enemy.HP -= act.POW;
        done = true;
    }
    else{
        for (int i = 0; i < s.nb_other; i++){
            if (equal(s.other[i].name, prompt, 0, s.other[i].name_length)){
                s.other[i].HP -= act.POW;
                done = true;
            }
        }
    }
    if (!done){
        printf("Target not found !\n");
    }
    return s;
}

stats execute_action(stats s, action act, int ch_id, int act_id){
    if (act.type == 'g'){
        if (act.POW > 0 && !equal(act.st.name, "stun", 0, 4)){
            if (s.nb_other == 0){
                s.enemy.HP -= act.POW;
            }
            else{
                s = action_when_many_enemies(s, act);
            }
            if (equal(act.st.name, "danger", 0, 6)){
                int pick = rand()%100;
                s.team[ch_id].HP -= Int(act.POW * pick / 100.);
                printf("\033[0;31m %s hurts themselves from the action \033[0;0m\n", s.team[ch_id].name);
            }
        }
        
        if (act.heal > 0){
            if (equal("defense", act.st.name, 0, 7)){
                if (ch_id < 5){
                    if (ch_id == 3 && s.nb_other == 2){
                        s.other[1].st.name = "defense";
                        s.other[1].st.end = s.turn + act.st.end;
                        if (act.heal == 100){
                            s.other[1].DEF = 100;
                        }
                        else{
                            s.other[1].DEF += act.heal;
                        }
                        printf("\033[0;32m %s has %d defense for %d turns ! \033[0;0m\n", s.other[1].name, s.other[1].DEF, act.st.end);
                    }
                    else{
                        s.team[ch_id].st.name = "defense";
                        s.team[ch_id].st.end = s.turn + act.st.end;
                        if (act.heal == 100){
                            s.team[ch_id].DEF = 100;
                        }
                        else{
                            s.team[ch_id].DEF += act.heal;
                        }
                        printf("\033[0;32m %s has %d defense for %d turns ! \033[0;0m\n", s.team[ch_id].name, s.team[ch_id].DEF, act.st.end);
                    }
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

        else if (equal("revive", act.st.name, 0, 6)){
            bool healed = false;
            char* entry = (char*)malloc(100*sizeof(char));
            while (!healed){
                printf("Who should you revive ?\n");
                fgets(entry, 100, stdin);
                for (int i = 0; i < 5; i++){
                    if (equal(s.team[i].name, entry, 0, s.team[i].name_length)){
                        if (s.team[i].HP > 0){
                            printf("This character isn't knocked down !\n");
                        }
                        else if (s.nb_other == 2 && i == 3){
                            printf("Can't revive Xhara while he's in betrayal state.\n");
                        }
                        else if (equal(s.team[i].st.name, "dead", 0, 4)){
                            printf("Can't revive a character whose SOUL has been taken.\n");
                        }
                        else{
                            s.team[i].HP = s.team[i].maxHP;
                            healed = true;
                        }
                    }
                }
                if (equal("none", entry, 0, 4)){
                    healed = true;
                }
            }
        }

        else if (!equal("normal", act.st.name, 0, 6) && !equal("defense", act.st.name, 0, 7) && !equal("danger", act.st.name, 0, 6)){    
            s = special_act(act, s);
        }
    }
    else if (act.type == 'l'){
        if (action_success(act)){
            printf("\033[0;32m Executing %s... \033[0;0m\n", act.name);

            if (act.POW > 0 && !equal(act.st.name, "boost", 0, 5)){
                if (s.nb_other == 0){
                    s.enemy.HP -= act.POW;
                }
                else{
                    s = action_when_many_enemies(s, act);
                }
            }

            else if (equal(act.st.name, "boost", 0, 5)){
                s.team[ch_id].POW *= 1.5;
                printf("%s has a %d POW now !\n", s.team[ch_id].name, s.team[ch_id].POW);
            }

            else if (equal("focus", act.st.name, 0, 5)){
                if (s.nb_other == 2){
                    s.other[1].st.name = "focus";
                    s.other[1].st.end = -1;
                }
                else{
                    s.team[ch_id].st.name = "focus";
                    s.team[ch_id].st.end = -1;
                }
            }
            else if (equal("smell", act.st.name, 0, 5)){
                char* prompt = (char*)malloc(100*sizeof(char));
                printf("How much time to focus (seconds) ? ");
                fgets(prompt, 100, stdin);
                if (!belongs(prompt[2], "0123456789", 10)){
                    int choice = convert(prompt[0], prompt[1]);
                    s.team[ch_id].smell = smell_scale(choice);
                }
                else{
                    s.team[ch_id].smell = smell_scale(100);
                }
                free(prompt);
            }
            else if (!equal("normal", act.st.name, 0, 6)){    
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
                if (s.nb_other == 0){
                    s.enemy.HP -= act.POW;
                }
                else{
                    s = action_when_many_enemies(s, act);
                }
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
    if (equal(ch.name, "Xhara", 0, 5)){
        return;
    }
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

stats enemy_attack(stats s, int ID){
    character Enemy;
    if (ID == -1){
        Enemy = s.enemy;
    }
    else{
        Enemy = s.other[ID];
    }
    
    if (!equal(Enemy.st.name, "stun", 0, 4) && !equal(Enemy.st.name, "rest", 0, 4)){
        assert_ennemy_stats(Enemy);
        action Action = choose_enemy_action(Enemy.actions);
        printf("%s attacks with %s !\n", Enemy.name, Action.name);
        bool dodge = false;
        bool shield = false;

        if (Action.POW > 0){
            if (Action.aim == 'a'){
                if (s.orb != NULL){
                    bool ok = false;
                    while (!ok){
                        char* prompt = (char*)malloc(100*sizeof(char));
                        printf("Attack power of the spirit ? ");
                        fgets(prompt, 100, stdin);
                        if (!belongs(prompt[0], "0123456789", 10)){
                            printf("invalid prompt !\n");
                        }
                        else{
                            ok = true; 
                            Action.POW = convert(prompt[0], prompt[1]);
                        }
                        free(prompt);
                    }
                }
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
                        bool protect = false;
                        for (int j = 0; j < 5; j++){
                            if (s.team[j].name == s.team[i].st.name){
                                s.team[j].HP -= entropy(Action.POW, 100, 40);
                                protect = true;
                            }
                        }
                        if (!protect){
                            if (s.orb == NULL){
                                char* ans = (char*)malloc(100*sizeof(char));
                                if (equal(Enemy.name, "Sensei", 0, 6)){
                                    printf("Did %s blocked the attack (y/N) ? ", s.team[i].name);
                                    fgets(ans, 100, stdin);
                                }
                                else{
                                    ans[0] = 'n';
                                }
                                if (ans[0] != 'y'){
                                    s.team[i].HP -= Int(0.01*(100 - s.team[i].DEF)*entropy(Action.POW, 100, 40));
                                }
                            }
                            else{
                                s.team[i].HP -= Int(0.01*(100 - s.team[i].DEF)*Action.POW)+1;
                            }
                        }
                    }
                }
            }

            else{
                character* target = &(s.team[0]);
                crew Alive;

                if (equal("normal", Enemy.st.name, 0, 6) || s.orb != NULL){
                    Alive = alive(s);
                    int targetID = rand()%Alive.N;
                    target = (Alive.team[targetID]);
                    for (int i = 0; i < 5; i++){
                        if (target->st.name == s.team[i].name){
                            target = &(s.team[i]);
                        }
                    }

                    if (target->DEF == 100){
                        printf("The target is %s, but they're protected !\n", target->name);
                        shield = true;
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
                        if (equal(s.team[i].name, Enemy.st.name, 0, s.team[i].name_length)){
                            target = (&(s.team[i]));
                            if (target->DEF == 100){
                                printf("\033[0;32m The enemy targets %s, but they're protected !\033[0;0m\n", target->name);
                                shield = true;
                            }
                            else{
                                printf("%s focuses %s !\n", Enemy.name, target->name);
                            }
                        }  
                    }
                }

                if (Action.superguard){
                    char* prompt = (char*)malloc(100*sizeof(char));
                    if (equal(Enemy.name, "Sensei", 0, 6)){
                        prompt[0] = 'y';
                    }
                    else{
                        printf("Does the character tries to superguard (y/N) ? ");
                        fgets(prompt, 100, stdin);
                    }
                    if (prompt[0] == 'y'){
                        printf("Attack dodged (y/N)? ");
                        fgets(prompt, 100, stdin);
                        if (equal("y", prompt, 0, 1)){
                            dodge = true;
                        }
                        else{
                            target->DEF = -100;
                        }
                    }
                    free(prompt);
                }
                
                if (!dodge){
                    if (!shield){
                        if (s.orb != NULL){
                            bool ok = false;
                            while (!ok){
                                char* prompt = (char*)malloc(100*sizeof(char));
                                printf("Attack power of the spirit ? ");
                                fgets(prompt, 100, stdin);
                                if (!belongs(prompt[0], "0123456789", 10)){
                                    printf("invalid prompt !\n");
                                }
                                else{
                                    ok = true; 
                                    Action.POW = convert(prompt[0], prompt[1]);
                                }
                                free(prompt);
                            }
                        }

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
                            if (s.orb == NULL){
                                target->HP -= Int(0.01*(100 - target->DEF)*entropy(Action.POW, 80, 30));
                                if (equal(Action.st.name, "weaken", 0, 6)){
                                    target->st.name = "weakenned";
                                    target->st.end = s.turn + 3;
                                    target->POW =  target->POW / 5;
                                    if (target->POW == 0){
                                        target->POW++;
                                    }
                                }
                            }
                            else{
                                target->HP -= Int(0.01*(100 - target->DEF)*Action.POW) + 1;
                            }
                        }
                    }
                }
                if (equal("normal", Enemy.st.name, 0, 6)){
                    free(Alive.team);
                }
            }
        } 

        if (Action.heal > 0 && !dodge && !shield){
            int recover = entropy(Action.heal, 100, 100);
            if (equal(Action.st.name, "Virus", 0, 5)){
                printf("\033[0;35mThe Virus recovers %d hearts ! \033[0;0m\n", recover);
                s.enemy.HP += recover;
            }
            else{
                printf("\033[0;35m%s recovers %d hearts ! \033[0;0m\n", Enemy.name, recover);
                Enemy.HP += recover;
            }
        }

        if (Action.POW == -1){
            if (equal(Action.name, "revolution", 0, 10)){
                double ratio = 0;
                for (int i = 0; i < 5; i++){
                    if (!(i == 3 && s.nb_other == 2)){
                        int add = 100*s.team[i].HP / s.team[i].maxHP;
                        ratio += add / 100.;
                    }
                }
                if (s.nb_other == 1){
                    ratio = ratio / 5.;
                }
                else{
                    ratio = ratio / 4.;
                }
                for (int i = 0; i < 5; i++){
                    if (s.team[i].HP > 0){
                        s.team[i].HP = ratio*s.team[i].maxHP;
                    }
                }
            }
        }

        if (equal(Action.st.name, "rage", 0, 4) || equal(Action.st.name, "reflect", 0, 7)){
            s.enemy.st.name = Action.st.name;
            s.enemy.st.end = Action.st.end;
        }

        if (equal(Action.st.name, "target", 0, 6)){
            character* target;
            crew Alive = alive(s);
            int targetID = rand()%Alive.N;
            target = (Alive.team[targetID]);
            for (int i = 0; i < 5; i++){
                if (target->st.name == s.team[i].name){
                    target = &(s.team[i]);
                }
            }
            s.enemy.st.name = target->name;
            s.enemy.st.end = s.turn + 2;
        }

        if (equal(Action.st.name, "confuse", 0, 7)){
            bool found_target = false;
            character* target;
            for (int i = 0; i < 5; i++){
                if (equal(s.enemy.st.name, s.team[i].name, 0, s.team[i].name_length) && s.team[i].HP > 0){
                    target = &(s.team[i]);
                    found_target = true;
                }
            }
            if (!found_target){
                crew Alive = alive(s);
                int targetID = rand()%Alive.N;
                target = (Alive.team[targetID]);
                for (int i = 0; i < 5; i++){
                    if (target->st.name == s.team[i].name){
                        target = &(s.team[i]);
                    }
                }
            }
            printf("The Virus targets %s !\n", target->name);

            bool can_confuse = false;
            if (equal(target->st.name, "clone", 0, 5)){
                int pick = rand()%3;
                if (pick == 0){
                    printf("The Virus attacks the left clone : is it the right one (y/N) ? ");
                    char* ans = (char*)malloc(100*sizeof(char));
                    fgets(ans, 100, stdin);
                    if (ans[0] == 'y'){
                        can_confuse = true;
                    }
                    free(ans);
                }
                else if (pick == 1){
                    printf("The Virus attacks the middle clone : is it the right one (y/N) ? ");
                    char* ans = (char*)malloc(100*sizeof(char));
                    fgets(ans, 100, stdin);
                    if (ans[0] == 'y'){
                        can_confuse = true;
                    }
                    free(ans);
                }
                else{
                    printf("The Virus attacks the right clone : is it the right one (y/N) ? ");
                    char* ans = (char*)malloc(100*sizeof(char));
                    fgets(ans, 100, stdin);
                    if (ans[0] == 'y'){
                        can_confuse = true;
                    }
                    free(ans);
                }
            }
            else{
                can_confuse = true;
            }
            if (can_confuse){
                target->st.name = "confuse";
                target->st.end = s.turn + Action.st.end;
                target->POW *= 5;
            }
        }

        for (int i = 0; i < 5; i++){
            if (equal(s.team[i].st.name, "focus", 0, 5)){
                s.team[i].st.name = "focus success";
                s.team[i].st.end = s.turn + 2;
            }
        }

        if (s.nb_other == 2){
            if (equal(s.other[1].st.name, "focus", 0, 5)){
                s.other[1].st.name = "focus success";
                s.other[1].st.end = s.turn + 2;
            }
        }

        if (s.orb != NULL){
            s = check_weakness(s);
        }

        if (ID == -1){
            s.enemy = Enemy;
        }
        else{
            if (ID == 0){
                Enemy.st.name = "rest";
                Enemy.st.end = s.turn + 2;
            }
            s.other[ID] = Enemy; 
        }
        return s;
    }
    else{
        printf("\033[0;31m %s recovers \033[0;0m\n", Enemy.name);
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

stats claim_SOUL(stats s){
    for (int i = 0; i < 5; i++){
        if (s.team[i].HP <= 0 && !equal(s.team[i].st.name, "dead", 0, 4)){
            s.enemy.HP += 100;
            printf("The Virus took %s's SOUL and became stronger !\n", s.team[i].name);
            s.team[i].st.name = "dead";
            s.team[i].st.end = -1;

            s.enemy.actions[0].POW *= 1.5;
            s.enemy.actions[0].heal *= 1.5;
            s.enemy.actions[3].POW *= 1.5;
        }
    }
    if (s.nb_other == 2){
        if (s.other[1].HP <= 0 && !equal(s.other[1].st.name, "dead", 0, 4)){
            s.enemy.HP += 100;
            printf("The Virus took %s's SOUL and became stronger !\n", s.other[1].name);
            s.other[1].st.name = "dead";
            s.other[1].st.end = -1;

            s.enemy.actions[0].POW *= 1.5;
            s.enemy.actions[0].heal *= 1.5;
            s.enemy.actions[3].POW *= 1.5;
        }
    }
    return s;
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
