#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "battle.h"

/* Checks if the battle reaches the end (i-e one party goes down)*/
bool end(stats s){
    if (s.enemy.HP <= 0){
        if (s.orb == NULL && s.other == NULL){
            printf("\033[0;32m The enemy is defeated !\033[0;32m\n");
            return true;
        }
        else if (s.orb == NULL){
            bool done = true;
            for (int i = 0; i < s.nb_other; i++){
                if (s.other[i].HP > 0){
                    done = false;
                }
            }
            if (done){
                printf("\033[0;32m Ennemies are defeated !\033[0;32m\n");
                return true;
            }
        }
    }
    else{
        if (!equal("Sensei", s.enemy.name, 0, 6)){
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
    else if (equal(retrieve, "Flavie", 0, 6)){
        st.name = "Flavie";
    }
    else if (equal(retrieve, "Haloise", 0, 7)){
        st.name = "Haloise";
    }
    else if (equal(retrieve, "Xhara", 0, 5)){
        st.name = "Xhara";
    }
    else if (equal(retrieve, "Clover", 0, 5)){
        st.name = "Clover";
    }
    else if (equal(retrieve, "danger", 0, 6)){
        st.name = "danger";
    }
    else if (equal(retrieve, "fire", 0, 4)){
        st.name = "fire";
    }
    else if (equal(retrieve, "ice", 0, 3)){
        st.name = "ice";
    }
    else if (equal(retrieve, "water", 0, 5)){
        st.name = "water";
    }
    else if (equal(retrieve, "light", 0, 5)){
        st.name = "light";
    }
    else if (equal(retrieve, "vegetal", 0, 7)){
        st.name = "vegetal";
    }
    else if (equal(retrieve, "gluton", 0, 6)){
        st.name = "gluton";
    }
    else if (equal(retrieve, "dark", 0, 4)){
        st.name = "dark";
    }
    else if (equal(retrieve, "human", 0, 5)){
        st.name = "human";
    }
    else if (equal(retrieve, "stone", 0, 5)){
        st.name = "stone";
    }
    else if (equal(retrieve, "shadow", 0, 6)){
        st.name = "shadow";
    }
    else if (equal(retrieve, "climate", 0, 7)){
        st.name = "climate";
    }
    else if (equal(retrieve, "sensei", 0, 6)){
        st.name = "sensei";
    }
    else if (equal(retrieve, "confuse", 0, 7)){
        st.name = "confuse";
    }
    else if (equal(retrieve, "weakenned", 0, 9)){
        st.name = "weakenned";
    }
    else if (equal(retrieve, "rage", 0, 4)){
        st.name = "rage";
    }
    else if (equal(retrieve, "reflect", 0, 7)){
        st.name = "reflect";
    }
    else if (equal(retrieve, "vulnerable", 0, 10)){
        st.name = "vulnerable";
    }
    else {
        st.name = "?";
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
    else if (equal(battle, "Virus", 0, 5)){
        s = final_initialize();
    }
    else if (equal(battle, "knight", 0, 6) || equal(battle, "sensei", 0, 6)){
        s = spirit_initialize(battle, check_string_length(battle), NULL_STATE());
    }
    else{
        free(battle);
        fclose(file);
        FILE* file2 = fopen("src/battle/data/state.txt", "r");
        char* element = (char*)malloc(10*sizeof(char));
        char* enemy = (char*)malloc(10*sizeof(char));
        char** strings = (char**)malloc(2*sizeof(char*));
        strings[0] = element;
        strings[1] = enemy;
        int* lengths = (int*)malloc(2*sizeof(int));
        int N = 2;
        fscanf(file2, "%s %s\n", element, enemy);
        lengths[0] = check_string_length(element);
        lengths[1] = check_string_length(enemy);
        if (equal(enemy, "spirit", 0, 6) || equal(enemy, "shell", 0, 5)){
            s = spirit_initialize(merge_strings(strings, N, lengths), lengths[0] + lengths[1] + 1, NULL_STATE());
            free(enemy);
            free(element);
        }
        else{
            free(enemy);
            free(element);
            printf("Unreconized battle !\n");
            stats null = {
                .team = NULL,
            };
            return null;
        }
        for (int i = 0; i < 5; i++){
            character ch = s.team[i];
            char* retrieve = (char*)malloc(100*sizeof(char));
            int* end = (int*)malloc(sizeof(int));
            fscanf(file2, "%d %d %d %s %d\n", &(ch.HP), &(ch.POW), &(ch.DEF), retrieve, end);
            ch.st = affect_state(retrieve, *end);
            s.team[i] = ch;
            free(retrieve);
            free(end);
        }
        character ch = s.enemy;
        char* retrieve = (char*)malloc(100*sizeof(char));
        int* end = (int*)malloc(sizeof(int));
        fscanf(file2, "%d %s %d\n", &(ch.HP), retrieve, end);
        ch.st = affect_state(retrieve, *end);
        s.enemy = ch; 

        fscanf(file2, "%d %d\n", &(s.turn), &(s.nb_other));
        free(retrieve);
        free(end);

        int* took = (int*)malloc(3*sizeof(int));
        fscanf(file2, "%d %d %d %d", &(took[0]), &(took[1]), &(took[2]), &(s.nb_spirit));
        s.took = took;

        fscanf(file2, "%d %d", &(s.orb[0]), &(s.orb[1]));

        fclose(file2);
        
        return s;
    }
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
    int* end = (int*)malloc(sizeof(int));
    fscanf(file, "%d %s %d\n", &(ch.HP), retrieve, end);
    ch.st = affect_state(retrieve, *end);
    s.enemy = ch; 

    fscanf(file, "%d %d\n", &(s.turn), &(s.nb_other));
    free(retrieve);
    free(end);
    for (int i = 0; i < s.nb_other; i++){
        character ch = s.other[i];
        char* retrieve = (char*)malloc(100*sizeof(char));
        int* end = (int*)malloc(sizeof(int));
        fscanf(file, "%d %d %d %s %d\n", &(ch.HP), &(ch.POW), &(ch.DEF), retrieve, end);
        ch.st = affect_state(retrieve, *end);
        s.other[i] = ch;
        free(retrieve);
        free(end);
        if (i == 1){
            s.other[i].name = "Xhara";
            s.other[i].name_length = 5;
            s.other[i].maxHP = 150;
            s.other[i].dice = 10;
            s.other[i].actions = malloc(2*sizeof(action));
            s.other[i].actions[0] = s.team[3].actions[1];
            s.other[i].actions[1] = s.team[3].actions[2];
            s.other[i].NOA = 2;
        }
    }
    if (s.orb != NULL){
        int* took = (int*)malloc(3*sizeof(int));
        fscanf(file, "%d %d %d %d", &(took[0]), &(took[1]), &(took[2]), &(s.nb_spirit));
        s.took = took;
        fscanf(file, "%d %d", &(s.orb[0]), &(s.orb[1]));
    }
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
    fprintf(file, "%d %s %d\n%d %d\n", ch.HP, ch.st.name, ch.st.end, s.turn, s.nb_other);

    for (int i = 0; i < s.nb_other; i++){
        character ch = s.other[i];
        fprintf(file, "%d %d %d %s %d\n", ch.HP, ch.POW, ch.DEF, ch.st.name, ch.st.end);
    }

    if (s.orb != NULL){
        fprintf(file, "%d %d %d %d\n%d %d\n", s.took[0], s.took[1], s.took[2], s.nb_spirit, s.orb[0], s.orb[1]);
    }
    fclose(file);
    return;
}

/* removes a state if the turn is right*/
stats reset_state(stats s){
    if (s.enemy.HP > s.enemy.maxHP){
        s.enemy.HP = s.enemy.maxHP;
    }

    if (s.other != NULL){
        for (int i = 0; i < s.nb_other; i++){
            if (s.other[i].HP > s.other[i].maxHP){
                s.other[i].HP = s.other[i].maxHP;
            }
            if (s.turn == s.other[i].st.end){
                if (equal(s.other[i].st.name, "defense", 0, 7)){
                    s.other[i].DEF = 0;
                }
                s.other[i].st.name = "normal";
            }
        }
    }

    if (s.turn == s.enemy.st.end){
        s.enemy.st.name = "normal";
    }
    for (int i = 0; i < 5; i++){
        if (s.turn == s.team[i].st.end){
            if (equal(s.team[i].st.name, "weakenned", 0, 9)){
                s.team[i].POW *= 5;
            }
            if (equal(s.team[i].st.name, "confuse", 0, 7)){
                s.team[i].POW = s.team[i].POW / 5;
            }
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
    if (equal(s.enemy.name, "Sensei", 0, 6)){
        printf("\033[0;37m");
        printf("\n*** turn %d ***\n", s.turn);
        int gardes[5] = {18, 8, 12, 16, 10};
        char* belts[5] = {"\033[0;37m", "\033[0;32m", "\033[0;34m", "\033[0;33m", "\033[0;36m"};
        
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

    else if (s.other != NULL){
        printf("\033[0;37m");
        printf("\n*** turn %d ***\n\033[0;31mENNEMIES\n", s.turn);
        
        printf("%s : \033[0;35m ♥ %d  ",s.enemy.name, s.enemy.HP); 
        life_bar(s.enemy);
        printf("\033[0;31m [%s]\n", s.enemy.st.name);

        for (int i = 0; i < s.nb_other; i++){
            if (s.other[i].HP <= 0){
                if (equal(s.other[i].st.name, "dead", 0, 4)){
                    printf("\033[0;31m%s : DEAD \033[0;0m\n", s.other[i].name);
                }
                else{
                    printf("\033[0;31m%s : DOWN \033[0;0m\n", s.other[i].name);
                }
            }
            else{
                printf("%s : \033[0;35m ♥ %d  ",s.other[i].name, s.other[i].HP); 
                life_bar(s.other[i]);
                printf("\033[0;31m [%s]\n", s.other[i].st.name);
            }
        }

        printf("\033[0;34m\n\nTEAM\n");
        for (int i = 0; i < 5; i++){
            if (s.team[i].HP < 0){
                s.team[i].HP = 0;
            }
            if (s.team[i].HP > s.team[i].maxHP){
                s.team[i].HP = s.team[i].maxHP;
            }
            if (s.team[i].HP == 0){
                if (equal(s.team[i].st.name, "dead", 0, 4)){
                    printf("\033[0;34m %s : DEAD \033[0;0m\n", s.team[i].name);
                }
                else{
                    printf("\033[0;34m %s : DOWN \033[0;0m\n", s.team[i].name);
                }
            }
            else{
                printf("\033[0;36m %s : \033[0;35m ♥ %d  ", s.team[i].name, s.team[i].HP);
                life_bar(s.team[i]);
                printf("\033[0;36m [%s] \033[0;0m\n", s.team[i].st.name);
            }
        }
    }

    else{
        printf("\033[0;37m");
        printf("\n*** turn %d ***\n", s.turn);
        
        printf("\033[0;31m \n%s : \033[0;35m ♥ %d  ",s.enemy.name, s.enemy.HP); 
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

        if (s.orb != NULL){
            char* arr[6] = {"None", "Fire", "Ice", "Water", "Light", "Vegetal"};
            if (s.orb[1] < 0){
                printf("\n\033[0;33m Orb state : {%s, %s}\033[0;0m\n", arr[s.orb[0]+1], arr[s.orb[1]+1]);
            }
            else{
                printf("\n\033[0;33m Orb state : {%s, %s} -> %s\033[0;0m\n", arr[s.orb[0]+1], arr[s.orb[1]+1], merge_magic(s.orb[0], s.orb[1]));
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

    if (s.orb != NULL){
        free(s.orb);
        free(s.took);
    }
}

void main(int argc, char *argv[]){
    srand(time(NULL));
    stats s;

    if (argc > 1){
        if (equal(argv[1], "restore", 0, 7)){
            printf("Restoring state...\n");
            s = restore_state(s);
            if (s.team == NULL){
                printf("\033[0;31mABORT\n");
                return;
            }
            
        }
        else if (equal(argv[1], "Dragon", 0, 6)){
            printf("Start of the battle against the dragon !\n");
            s = dragon_initialize();
        }
        else if (equal(argv[1], "Sensei", 0, 6)){
            printf("Start of the battle against the sensei !\n");
            s = sensei_initialize();
        }
        else if (equal(argv[1], "Spirit", 0, 6)){
            printf("Start of the battle against the spirits !\n");
            s = spirit_initialize(NULL, 0, NULL_STATE());
            int* took = (int*)malloc(3*sizeof(int));
            for (int i = 0; i < 3; i++){
                took[i] = -1;
            }
            s.took = took;
        }
        else if (equal(argv[1], "Final", 0, 5)){
            printf("Start of the final battle !\n");
            s = final_initialize();
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
    for (int i = 0; i < s.nb_other; i++){
        assert_ennemy_stats(s.other[i]);
    }
    bool the_end = false;
    char* last = (char*)malloc(100*sizeof(char));
    while (!end(s) || the_end){
        if (s.orb != NULL){
            if (s.enemy.HP <= 0){
                if (s.nb_spirit == 3){
                    printf("\033[0;32mThe spirits are defeated !\033[0;32m\n");
                    free_all(s);
                    return;
                }
                else{
                    char* state_names[12] = {"fire", "ice", "water", "light", "vegetal", "gluton", "dark", "human", "stone", "shadow", "climate", "sensei"};
                    int name_lengths[12] = {11, 10, 12, 12, 14, 13, 11, 6, 11, 11, 14, 6};
                    int i = 0;
                    while(!equal(state_names[i], s.enemy.st.name, 0, name_lengths[i])){
                        i++;
                    }
                    s.took[s.nb_spirit] = i;
                    s.nb_spirit++;
                    free(s.enemy.actions);
                    s = choose_spirit(s, NULL, 0, NULL_STATE());
                    printf("Spirit n° %d\n", s.nb_spirit);
                }
            } 
        }

        s = reset_state(s);
        print_state(s);
        write_state(s);

        char* prompt = (char*)malloc(100*sizeof(char));
        printf("> ");
        fgets(prompt, 100, stdin);

        if (equal("last", prompt, 0, 4)){
            for (int i = 0; i < 100; i++){
                prompt[i] = last[i];
            }
        }
        else{
            for (int i = 0; i < 100; i++){
                last[i] = prompt[i];
            }
        }

        if (equal("attack", prompt, 0, 6)){
            bool done = false;
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 7, 7+s.team[i].name_length) && (s.nb_other < 2 || (s.nb_other == 2 && i != 3))){
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
                        else if (s.other != NULL){
                            character* target = (character*)malloc(sizeof(character));
                            target = NULL;
                            int target_id = -1;
                            bool ok = false;
                            if (equal(s.enemy.name, prompt, 15 + s.team[i].name_length, 15 + s.team[i].name_length + s.enemy.name_length)){
                                target = &(s.enemy);
                                ok = true;
                            }
                            else{
                                for (int j = 0; j < s.nb_other; j++){
                                    if (equal(s.other[j].name, prompt, 15 + s.team[i].name_length, 15 + s.team[i].name_length + s.other[j].name_length)){
                                         target = &(s.other[j]);
                                         target_id = j;
                                         ok = true;
                                    }
                                }
                            }
                            if (!ok){
                                printf("target not found !");
                            }
                            else{
                                if (target_id == -1){
                                    char d = prompt[16 + s.team[i].name_length + s.enemy.name_length];
                                    char u = prompt[17 + s.team[i].name_length + s.enemy.name_length];
                                    int dice = convert(d, u);
                                    int att = attack(s.team[i], dice_range(s.team[i], dice));
                                    bool attack_done = false;
                                    if (equal(s.team[i].st.name, "confuse", 0, 7)){
                                        if (happening(50)){
                                            crew cibles = alive(s);
                                            character* victime = cibles.team[rand()%cibles.N];
                                            victime->HP -= att;
                                            printf("%s got confused !\n", s.team[i].name);
                                            attack_done = true;
                                            free(cibles.team);
                                        }
                                    }
                                    if(!attack_done){
                                        s.enemy.HP -= att;
                                        if (equal(s.enemy.st.name, "reflect", 0, 7)){
                                            s.team[i].HP -= att/2.;
                                        }
                                    }
                                }
                                else{
                                    if (s.other[target_id].DEF == 100){
                                        printf("Attack missed !\n");
                                    }
                                    else{
                                        printf("id: %d def:%d\n", target_id, s.other[target_id].DEF);

                                        char d = prompt[16 + s.team[i].name_length + s.other[target_id].name_length];
                                        char u = prompt[17 + s.team[i].name_length + s.other[target_id].name_length];
                                        int dice = convert(d, u);
                                        int att = attack(s.team[i], dice_range(s.team[i], dice));
                                        bool attack_done = false;
                                        if (equal(s.team[i].st.name, "confuse", 0, 7)){
                                            if (happening(50)){
                                                crew CIBLES = alive(s);
                                                character* VICTIME = CIBLES.team[rand()%CIBLES.N];
                                                VICTIME ->HP -= att;
                                                printf("%s got confused !\n", s.team[i].name);
                                                attack_done = true;
                                                free(CIBLES.team);
                                            }
                                        }
                                        if(!attack_done){
                                            printf("POW : %d\n", att);
                                            s.other[target_id].HP -= att;
                                        }
                                        if (equal(s.other[target_id].st.name, "focus", 0, 5)){
                                            printf("Focus failed !\n");
                                            s.other[target_id].st.name = "normal";
                                            s.other[target_id].st.end = -1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (equal(s.enemy.name, prompt, 7, 7 + s.enemy.name_length) || equal("Spirit", prompt, 7, 13)){
                done = true;
                if (s.nb_other > 0){
                    s = claim_SOUL(s);
                }
                s = enemy_attack(s, -1);  

                // reset orb   
                if (s.orb != NULL){
                    s.orb[0] = -1;
                    s.orb[1] = -1;
                }   

                if (s.nb_other == 0){
                    s.turn++;   
                }          
            }

            for (int i = 0; i < s.nb_other; i++){
                if (equal(s.other[i].name, prompt, 7, 7 + s.other[i].name_length)){
                    if (equal(s.other[i].name, "Xhara", 0, 5)){
                        if (equal(s.other[i].st.name, "stun", 0, 4)){
                            printf("Xhara is stunned for this turn!\n");
                            done = true;
                        }
                        else{
                            for (int j = 0; j < 5; j++){
                                if (equal(s.team[j].name, prompt, 20, 20 + s.team[j].name_length)){
                                    done = true;
                                    char d = prompt[21 + s.team[j].name_length];
                                    char u = prompt[22 + s.team[j].name_length];
                                    int dice = convert(d, u);
                                    bool attack_done = false;
                                    for (int k = 0; k < 5; k++){
                                        if (equal(s.team[j].st.name, s.team[k].name, 0, s.team[k].name_length)){
                                            s.team[k].HP -= 1.5*attack(s.other[i], dice);
                                            attack_done = true;
                                        }
                                    }
                                    if (!attack_done){
                                        if (equal(s.team[j].st.name, "clone", 0, 5)){
                                            printf("Did Xhara target the genuine Clover (y/N) ? ");
                                            char* ans = (char*)malloc(100*sizeof(char));
                                            fgets(ans, 100, stdin);
                                            if (ans[0] == 'y'){
                                                s.team[j].HP -= attack(s.other[i], dice);
                                            }
                                            free(ans);
                                        }
                                        else{
                                            s.team[j].HP -= attack(s.other[i], dice);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else{
                        done = true;
                        s = enemy_attack(s, i); 
                    }
                    if (s.nb_other == 0){
                        s.turn++;
                    }
                }
            }
            
            if (!done){
                printf("Target not found !\n");
            }
        }

        else if (equal("action", prompt, 0, 6)){
            bool done = false;
            bool found = false;
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 7, 7+s.team[i].name_length)){
                    done = true;
                    if (s.team[i].HP <= 0 && ((s.nb_other < 2) || (s.nb_other == 2  && i != 3))){
                        printf("\033[0;31m You can't act with a K-O character \033[0;0m\n");
                    }
                    else if (equal("protect", prompt, 8+s.team[i].name_length, 15+s.team[i].name_length)){
                        if (s.nb_other == 2 && i == 3){
                            printf("Action not available\n");
                        }
                        else{
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
        else if (equal("betray", prompt, 0, 6)){
            if (s.nb_other == 0){
                printf("Xhara can't betray the team for this fight !\n");
            }
            else if (s.nb_other == 2){
                printf("Already done.\n");
            }
            else{
                s.nb_other = 2;
                character Xhara = s.team[3];
                s.team[3].st.name = "dead";
                s.team[3].st.end = -1; 

                s.other[1] = Xhara;
                
                s.team[3].HP = 0;
            }
        }
        else if (equal("buff", prompt, 0, 4)){
            if (s.nb_other < 2){
                s.team[3].maxHP *= 1.5;
                s.team[3].POW *= 1.5;
                s.team[3].HP = s.team[3].maxHP;
            }
            else{
                s.other[1].maxHP *= 1.5;
                s.other[1].POW *= 1.5;
                s.other[1].HP = s.other[1].maxHP;
            }
        }
        else if (equal("upgrade", prompt, 0, 7)){
            for (int i = 0; i < 5; i++){
                if (i == 3){
                    s.team[i].POW *= 5;
                    s.team[i].NOA = 3;
                    if (s.nb_other == 2){
                        s.other[1].POW *= 5;
                        s.other[1].NOA = 3;
                    }
                }
                else{
                    s.team[i].POW *= 10;
                    s.team[i].NOA = 4;
                }
            }
            printf("\033[0;32m Upgrade done !\n");
        }
        else if (equal("turn", prompt, 0, 4)){
            s.turn++;
        }
        else if (equal("damage", prompt, 0, 6)){
            bool done = false;
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 7, 7+s.team[i].name_length)){
                    char* val = (char*)malloc(4*sizeof(char));
                    for (int k = 0; k < 4; k++){
                        val[k] = prompt[8+s.team[i].name_length+k];
                    }
                    s.team[i].HP -= convert1000(val);
                    free(val);
                    if (!(i == 3 && s.nb_other == 2)){
                        done = true;
                    }
                }
            }
            if (!done){
                if (equal(s.enemy.name, prompt, 7, 7+s.enemy.name_length)){
                    char* val = (char*)malloc(4*sizeof(char));
                    for (int k = 0; k < 4; k++){
                        val[k] = prompt[8+s.enemy.name_length+k];
                    }
                    s.enemy.HP -= convert1000(val);
                    free(val); 
                    done = true;
                }
                else if (equal("enemy", prompt, 7, 12)){
                    char* val = (char*)malloc(4*sizeof(char));
                    for (int k = 0; k < 4; k++){
                        val[k] = prompt[13+k];
                    }
                    s.enemy.HP -= convert1000(val);
                    free(val); 
                    done = true;
                }
                else{
                    for (int i = 0; i < s.nb_other; i++){
                        if (equal(s.other[i].name, prompt, 7, 7+s.other[i].name_length)){
                            char* val = (char*)malloc(4*sizeof(char));
                            for (int k = 0; k < 4; k++){
                                val[k] = prompt[8+s.other[i].name_length+k];
                            }
                            s.other[i].HP -= convert1000(val);
                            free(val); 
                            done = true;
                        }
                    }
                }
            }
            if (!done){
                printf("\033[0;31mCharacter not found !\033[0;0m\n");
            }
        }
        else if (equal("heal", prompt, 0, 4)){
            bool done = false;
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 5, 5+s.team[i].name_length)){
                    char* val = (char*)malloc(4*sizeof(char));
                    for (int k = 0; k < 4; k++){
                        val[k] = prompt[6+s.team[i].name_length+k];
                    }
                    printf("%d\n", convert1000(val));
                    s.team[i].HP += convert1000(val);
                    free(val);
                    if (!(i == 3 && s.nb_other == 2)){
                        done = true;
                    }
                }
            }
            if (!done){
                if (equal(s.enemy.name, prompt, 5, 5+s.enemy.name_length)){
                    char* val = (char*)malloc(4*sizeof(char));
                    for (int k = 0; k < 4; k++){
                        val[k] = prompt[6+s.enemy.name_length+k];
                    }
                    s.enemy.HP += convert1000(val);
                    free(val); 
                    done = true;
                }
                else{
                    for (int i = 0; i < s.nb_other; i++){
                        if (equal(s.other[i].name, prompt, 5, 5+s.other[i].name_length)){
                            char* val = (char*)malloc(4*sizeof(char));
                            for (int k = 0; k < 4; k++){
                                val[k] = prompt[6+s.other[i].name_length+k];
                            }
                            s.other[i].HP += convert1000(val);
                            free(val); 
                            done = true;
                        }
                    }
                }
            }
            if (!done){
                printf("\033[0;31mCharacter not found !\033[0;0m\n");
            }
        }
        else if (equal("revive", prompt, 0, 6)){
            bool done = false;
            for (int i = 0; i < 5; i++){
                if (equal(s.team[i].name, prompt, 7, 7+s.team[i].name_length)){
                    if (!(i == 3 && s.nb_other == 2)){
                        printf("hi\n");
                        if (s.team[i].HP == 0){
                            s.team[i].HP = s.team[i].maxHP;
                        }
                        else{
                            printf("The character isn't knocked down !\n");
                        }
                        done = true;
                    }
                }
            }
            if (!done){
                if (equal(s.enemy.name, prompt, 7, 7 + s.enemy.name_length)){
                    done = true;
                    if (s.enemy.HP == 0){
                        s.enemy.HP = s.enemy.maxHP;
                    }
                    else{
                        printf("The character isn't knocked down !\n");
                    }
                }
                else{
                    for (int i = 0; i < s.nb_other; i++){
                        if (equal(s.other[i].name, prompt, 7, 7 + s.other[i].name_length)){
                            done = true;
                            if (s.other[i].HP <= 0){
                                s.other[i].HP = s.other[i].maxHP;
                            }
                            else{
                                printf("The character isn't knocked down !\n");
                            }
                        }
                    }
                }
            }
        }
        else{
            printf("Unrecognized prompt\n");
        }
        free(prompt);
    }
    free_all(s);
}