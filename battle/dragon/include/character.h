#ifndef CHARACTER_H
#define CHARACTER_H

#include "util/include/character_base.h"
#include "util/include/action.h"

#define PARTY_LENGTH 5
#define N_ACTIONS 3

typedef struct character {
    CharacterBase base;
    const unsigned int pow;
    Action* actions;
} Character;

#endif