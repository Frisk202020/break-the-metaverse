#include "dragon/include/game_manager.h"

const char* INVALID_PARTY = "Invalid party id :";

void derek_action(GameManager* gm, unsigned int action_id) {
    switch(action_id) {
        case 0:
            // ask prompt > "which target" > apply state
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void flavie_action(GameManager* gm, unsigned int action_id) {
    switch(action_id) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void haloise_action(GameManager* gm, unsigned int action_id) {
    switch(action_id) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void clover_action(GameManager* gm, unsigned int action_id) {
    switch(action_id) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void xhara_action(GameManager* gm, unsigned int action_id) {
    switch(action_id) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

const char* action(
    GameManager* gm, 
    unsigned int party_id, unsigned int action_id
) {
    char* err = NULL;

    if (party_id >= PARTY_LENGTH) return "Invalid party member id %d";
    if (action_id >= N_ACTIONS) return "Invalid action id";

    switch(party_id) {
        case 0: derek_action(gm, action_id); break;
        case 1: flavie_action(gm, action_id); break;
        case 2: haloise_action(gm, action_id); break;
        case 3: clover_action(gm, action_id); break;
        case 4: xhara_action(gm, action_id); break;
    }

    return NULL;
}