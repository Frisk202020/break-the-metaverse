#ifndef CHARACTER_H
#define CHARACTER_H

#include "character_base.h"
#include "action.h"

#define PARTY_LENGTH 5
#define N_ACTIONS 3

typedef struct character {
    CharacterBase base;
    const unsigned int pow;
    Action actions[N_ACTIONS];
} Character;

Character character_init(
    const char* name, const unsigned int hp, 
    const unsigned int pow, Action actions[3]
);

Character dragon_init();

#endif