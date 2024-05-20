#ifndef BATTLE
#define BATTLE

#include <stdbool.h>

typedef struct{
    char* name;
    int POW;
    int heal;
    char aim; // Indiv (i) or All (a)
    bool superguard; // utilized for enemies. Set to true if the attack is dodgeable
}action;

typedef struct{
    char* name;
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
stats enemy_attack(stats* s_p);
crew alive(stats s);

//from battle.c
bool end(stats s);
void print_state(stats* s);

#endif