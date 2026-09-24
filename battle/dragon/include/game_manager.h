#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <pthread.h>
#include "character.h"

typedef struct game_manager {
    Character party[PARTY_LENGTH];
    Character dragon;

    int reset_state[PARTY_LENGTH];
    unsigned int turn;

    pthread_mutex_t mutex;
} GameManager;

const char* action(GameManager* gm, unsigned int party_id, unsigned int action_id);

#endif