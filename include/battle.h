#ifndef BATTLE
#define BATTLE

#include <stdbool.h>

typedef struct{
    char* name;
    int name_length;
    int POW;
    int heal;
    char aim; // types Indiv (i) or All (a) for the enemy ; types Garanted (g) or luck-based (l) for the party. Garanded actions are 1 time use
    bool superguard; // utilized for enemies. Set to true if the attack is dodgeable
    int odd; // probability for the action to be picked from the enemy ; probability for a luck-based action to succeed for the party
}action;

typedef struct{
    char* name;
    int name_length;
    int maxHP;
    int HP;
    int POW;
    int dice;
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
}stats;

//from utilities.c
int Int(double x);
int entropy(int value, int min, int var);
bool equal(char* s, char* prompt, int d, int e);
bool belongs(char c, char* s, int N);
int convert(char tenth, char unit);

//from dragon.c
stats dragon_initialize();

//from attack.c
int dice_range(character ch, int result);
int attack(character ch, int dice);
bool action_success(action act);
stats execute_action(stats* s_p, action act, int ch_id, int act_id);
void assert_ennemy_stats(character ch);
action choose_enemy_action(action* acts);
stats enemy_attack(stats* s_p);
crew alive(stats s);

//from battle.c
bool end(stats s);
void print_state(stats* s);

#endif