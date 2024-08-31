#ifndef BATTLE
#define BATTLE

#include <stdbool.h>

typedef struct{
    char* name;
    int end;
}state;

typedef struct{
    char* name;
    int name_length;
    int POW;
    int heal; // utilized for heal and defense purposes
    state st;
    char aim; // types Indiv (i) or All (a) or Enemy (e) 
    char type; // types Garanted (g), luck-based (l) or real-life (r) for the party. (g) actions are 1 time use, (r) actions require a real action in the game to succed.
    bool superguard; // utilized for enemies. Set to true if the attack is dodgeable
    int odd; // probability for the action to be picked from the enemy ; probability for a luck-based action to succeed for the party
}action;

typedef struct{
    char* name;
    int name_length;
    int maxHP;
    int HP;
    int POW;
    int DEF;
    state st;
    state smell; // for sensei fight
    int dice; // for dragon fight
    action* actions;
    int NOA; // Number Of Actions
}character;

typedef struct{
    int N;
    character** team;
}crew; // utilized to describe a non-complete crew

typedef struct{
    character* team;
    character enemy;
    character* other; //used for final battle
    int nb_other;
    int turn;
    int* orb; //used for spirit fight
    int nb_spirit;
    int* took;
}stats;

//from utilities.c
int Int(double x);
int entropy(int value, int min, int var);
bool equal(char* s, char* prompt, int d, int e);
bool belongs(char c, char* s, int N);
bool In(int* array, int N, int pick);
int convert(char tenth, char unit);
int convert1000(char* prompt);
bool happening(int odd);
int check_string_length(char* string);
char* merge_strings(char** strings, int N, int* lengths);

//from dragon.c
stats dragon_initialize();

//from sensei.c
stats sensei_initialize();
state smell_scale(int choice);

//from spirit.c
state NULL_STATE();
char* merge_magic(int i, int j);
character create_spirit(char* name, int name_length, state st);
stats choose_spirit(stats s, char* name, int name_length, state st);
stats spirit_initialize(char* spirit, int name_length, state new_state);
stats check_weakness(stats s);

//from final.c
stats final_initialize();

//from attack.c
int dice_range(character ch, int result);
int attack(character ch, int dice);
bool action_success(action act);
stats special_act(action act, stats s);
stats execute_action(stats s, action act, int ch_id, int act_id);
void assert_ennemy_stats(character ch);
action choose_enemy_action(action* acts);
stats enemy_attack(stats s, int ID);
crew alive(stats s);
stats action_when_many_enemies(stats s, action act);
stats claim_SOUL(stats s);

//from battle.c
bool end(stats s);
state affect_state(char* retrieve, int end);
stats restore_state(stats s);
void write_state(stats s);
stats reset_state(stats s_p);
void print_state(stats s);

#endif