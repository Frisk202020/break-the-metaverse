#include <iostream>
#include "battle.h"

/*
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
*/

/*
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
*/

/*
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
*/

int main(int argc, char** argv) {
    srand(time(NULL));
    Stats battle;
    int battle_id = 0; // instead of comparing strings many times
    if (argc < 2) {std::cout << "Please prompt the battle to launch !\n"; return 0;}

    std::string to_launch = std::string (argv[1]);
    if (to_launch == "Dragon") {
        battle = Stats::dragon_initializer();
    } else if (to_launch == "Sensei") {
        battle_id = 1;
    } else if (to_launch == "Spirit") {
        battle_id = 2;
    } else if (to_launch == "Final") {
        battle_id = 3;
    } else {
        std::cout << "Unrecognized battle -- ABORT\n"; return 0;
    }
    std::cout << battle_id << '\n';
    bool end = false;
    std::string prompt;
    do {
        if (to_launch == "Spirit") {}

        battle.update_stats();
        battle.print_state();
        // battle.write_state();
        std::cout << "> ";
        std::getline(std::cin, prompt);
        std::vector<std::string> args = split(prompt, " ");

        // if prompt == "last" (...)

        if (args[0] == "exit") {
            end = true;
            continue;
        }

        if (args[0] == "attack") {
            switch (battle_id) {
                case 0:
                    if (args.size() < 2) {std::cout << "Not enough arguments in your prompt\n"; continue;}
                    if (args[1] == "Dragon") {battle.default_enemy_attack(); continue;} // turn increments when casting default_enemy attack

                    if (args.size() < 3) {std::cout << "Not enough arguments in your prompt\n"; continue;}
                    try {
                        int dice = parse_int(args[2]);
                        battle.attack_dragon_battle(args[1], dice);
                        continue;
                    }
                    catch (std::invalid_argument &e) {std::cout << "Can't parse the dice result\n"; continue;}
                default: std::cout << "Default case should not be reached\n"; continue;
            }
            continue;
        }

        if (args[0] == "action") {
           if (args.size() < 3) { std::cout << "Invalid action command\n"; continue; }
           if (args.size() < 4) { battle.execute_action(args[2], args[1], ""); continue; }
           battle.execute_action(args[2], args[1], args[3]); continue;
        }

        /* Debug commands */
        if (args[0] == "turn") {
            battle.__debug__increment_turn();
            continue;
        }

        if (args[0] == "damage") {
            if (args.size() < 3) {std::cout << "Not enough arguments in your prompt\n"; continue;}
            try {
                int hp = parse_int(args[2]);
                battle.__debug__manage_hp(args[1], -hp);
                continue;
            }
            catch (std::invalid_argument &e) {std::cout << "Can't parse the gp value\n"; continue;}
        }

        if (args[0] == "heal") {
            if (args.size() < 3) {std::cout << "Not enough arguments in your prompt\n"; continue;}
            try {
                int hp = parse_int(args[2]);
                battle.__debug__manage_hp(args[1], hp);
                continue;
            }
            catch (std::invalid_argument &e) {std::cout << "Can't parse the hp value\n"; continue;}
        }

        if (args[0] == "revive") {
            if (args.size() < 2) {std::cout << "Not enough arguments in your prompt\n"; continue;}
            battle.__debug__revive(args[1]); continue;
        }

        std::cout << "Unrecognized command\n";
    } while (!end && !battle.is_end());


    return 0;
}
