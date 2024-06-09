#include <stdio.h>
#include <stdlib.h>
#include "battle.h"

char* merge_magic(int i, int j){
    char* one[5] = {"fire", "water", "fume", "burst", "poison"};
    char* two[5] = {"water", "ice", "sculpture", "beam", "darkness"};
    char* three[5] = {"fume", "sculpture", "water", "heal", "plant"};
    char* four[5] = {"burst", "beam", "heal", "light", "lila"};
    char* five[5] = {"poison", "darkness",  "plant", "lila", "vegetal"};
    char** magic[5] = {one, two, three, four, five};

    return magic[i][j];
}

character create_spirit(char* name, int name_length, state st){
    character Spirit = {
        .name = name,
        .name_length = name_length,
        .maxHP = 20,
        .HP = 20,
        .POW = 0,
        .DEF = 100,
        .st = st,
        .actions = malloc(1*sizeof(action)),
        .NOA = 1,
    };

    action attack = {
        .name = "attack",
        .name_length = 6,
        .POW = 30,
        .heal = 0,
        .st = Spirit.st,
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
    };

    Spirit.actions[0] = attack;
    return Spirit;
}

stats choose_spirit(stats s, int* took, int took_len){
    char* choices[12] = {"fire spirit", "ice spirit", "water spirit", "light spirit", "vegetal spirit", "gluton spirit", "dark shell", "knight", "solid shell", "dark spirit", "climate spirit", "sensei"};
    int name_lengths[12] = {11, 10, 12, 12, 14, 13, 11, 6, 11, 11, 14, 6};
    char* state_names[12] = {"fire", "ice", "water", "light", "vegetal", "gluton", "dark", "human", "stone", "shadow", "climate", "sensei"};
    int state_lengths[12] = {4, 3, 5, 5, 7, 6, 4, 5, 5, 6, 7, 6};
    int state_durations[12] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    char* weaknesses[12] = {"water", "fire", "fire", "darkness", "feu", "fume", "burst", "poison", "scuplture", "beam", "plant", "lila"};
    int r = rand()%12;
    while (In(took, took_len, r)){
        r = rand()%12;
    }
    state new_state = {
        .name = state_names[r],
        .end = state_durations[r],
    };
    character new_spirit = create_spirit(choices[r], name_lengths[r], new_state);
    s.enemy = new_spirit;

    return s;
}

stats spirit_initialize(){

    character Derek = { 
        .name = "Derek",
        .name_length = 5,
        .maxHP = 100,
        .HP = 100,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "fire",
            .end = -1,
        },
        .actions = malloc(2*sizeof(action)),
        .NOA = 2,
    };

    action taser = {
        .name = "taser",
        .name_length = 5,
        .POW = 1,
        .heal = 0,
        .st = {
            .name = "stun",
            .end = 1,
        },
        .aim = 'e',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : stuns the enemy for the current turn
    };

    action magic = {
        .name = "magic",
        .name_length = 5,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = 1,
        },
        .aim = 'e',
        .type = 'l',
        .superguard = false,
        .odd = 100,
        // effect : adds the magic of the character to the orb
    };
    
    Derek.actions[0] = taser;  

    character Flavie = {
        .name = "Flavie",
        .name_length = 6,
        .maxHP = 100,
        .HP = 100,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "ice",
            .end = -1,
        },
        .actions = malloc(2*sizeof(action)),
        .NOA = 2,
    };

    action hack = { 
        .name = "hack",
        .name_length = 4,
        .POW = 10,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'e',
        .type = 'r',
        .superguard = false,
        .odd = 100,
        // effect : hack the code of the battle to do insane dammage. 
    };

    Flavie.actions[0] = hack;

    character Haloise = {
        .name = "Haloise",
        .name_length = 7,
        .maxHP = 100,
        .HP = 100,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "water",
            .end = -1,
        },
        .actions = malloc(2*sizeof(action)),
        .NOA = 2,
    };

    action encyclopedia = { 
        .name = "encyclopedia",
        .name_length = 12,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'e',
        .type = 'r',
        .superguard = false,
        .odd = 100,
        // effect : retrieve information of the enemy 
    };

    Haloise.actions[0] = encyclopedia;

    character Xhara = { 
        .name = "Xhara",
        .name_length = 5,
        .maxHP = 100,
        .HP = 100,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "light",
            .end = -1,
        },
        .actions = malloc(2*sizeof(action)),
        .NOA = 2,
    };

    action betrayal = { 
        .name = "betrayal",
        .name_length = 8,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : high damage output, but the character may receive damage
    };

    Xhara.actions[0] = betrayal;

    character Clover = { 
        .name = "Clover",
        .name_length = 6,
        .maxHP = 100,
        .HP = 100,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "vegetal",
            .end = -1,
        },
        .actions = malloc(2*sizeof(action)),
        .NOA = 2,
    };

    action fake = { 
        .name = "fake",
        .name_length = 4,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "clone",
            .end = 3,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
    };

    Clover.actions[0] = fake;
    
        // effect : Clover creates 2 fake copies of himself that the enemy can attack instead of him. For each turn, he should choose left, right or middle, and the enemy chooses randomly one of the copies
    character* team = (character*)malloc(5*sizeof(character));
    team[0] = Derek;
    team[1] = Flavie;
    team[2] = Haloise;
    team[3] = Xhara;
    team[4] = Clover;

    stats s = {
        .team = team,
        .turn = 1,
    };

    for (int i = 0; i < 5; i++){
        magic.st.name = s.team[i].st.name;
        s.team[i].actions[1] = magic;
    }

    s = choose_spirit(s, NULL, 0);

    s.orb = malloc(2*sizeof(int));
    s.orb[0] = -1;
    s.orb[1] = -1;
    return s;
}