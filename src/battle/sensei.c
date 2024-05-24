#include <stdlib.h>
#include "battle.h"

/* Initialize the stats for the dragon fight*/
stats sensei_initialize(){
    character Derek = { 
        .name = "Derek",
        .name_length = 5,
        .maxHP = 20,
        .HP = 20,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(1*sizeof(action)),
        .NOA = 1,
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

    
    Derek.actions[0] = taser;  

    character Flavie = {
        .name = "Flavie",
        .name_length = 6,
        .maxHP = 120,
        .HP = 120,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(1*sizeof(action)),
        .NOA = 1,
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
        .maxHP = 80,
        .HP = 80,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(1*sizeof(action)),
        .NOA = 1,
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
        .maxHP = 40,
        .HP = 40,
        .POW = 1,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(1*sizeof(action)),
        .NOA = 1,
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
            .name = "normal",
            .end = -1,
        },
        .actions = malloc(1*sizeof(action)),
        .NOA = 1,
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

    character Sensei = {
        .name = "Sensei",
        .name_length = 6,
        .maxHP = 20,
        .HP = 20,
        .POW = 0,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .dice = 0,
        .actions = malloc(3*sizeof(action)),
        .NOA = 3,
    };

    action vertical = {
        .name = "vertical swing",
        .name_length = 14,
        .POW = 5,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'i',
        .superguard = true,
        .odd = 00,
    };
    action horizontal = {
        .name = "horizontal swing",
        .name_length = 17,
        .POW = 5,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'i',
        .superguard = true,
        .odd = 0,
    };
    action kamehameha = {
        .name = "kamehameha",
        .name_length = 10,
        .POW = 20,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'a',
        .superguard = true,
        .odd = 100,
    };

    Sensei.actions[0] = horizontal;
    Sensei.actions[1] = vertical;
    Sensei.actions[2] = kamehameha;

    stats s = {
        .team = team,
        .enemy = Sensei,
        .turn = 1,
    };

    return s;
}