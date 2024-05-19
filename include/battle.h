#ifndef BATTLE
#define BATTLE

#include <stdbool.h>

typedef struct{
    char* name;
    int HP;
    int POW;
    int dice;
}character;

typedef struct{
    character* team;
    character enemy;
}stats;

//from utilities.c
int Int(double x);
bool equal(char* s, char* prompt, int d, int e);
bool belongs(char c, char* s, int N);
int convert(char tenth, char unit);

//from dragon.c
stats dragon_initialize();

//from attack.c
int dice_range(character ch, int result);
int attack(character ch, int dice);

//from battle.c
bool end(stats s);
void print_state(stats s);

#endif