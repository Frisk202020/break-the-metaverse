#include <stdlib.h>
#include "battle.h"

/* Initialize the stats for the dragon fight*/
stats dragon_initialize(){
    character Derek = { //Derek is a knight
        .name = "Derek",
        .name_length = 5,
        .maxHP = 250,
        .HP = 250,
        .POW = 50,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .dice = 6,
        .actions = malloc(3*sizeof(action)),
        .NOA = 3,
    };

    action taser = {
        .name = "taser",
        .name_length = 5,
        .POW = 10,
        .heal = 0,
        .st = {
            .name = "stun",
            .end = 1,
        },
        .aim = 'e',
        .type = 'l',
        .superguard = false,
        .odd = 30,
        // effect : stuns the enemy for the current turn
    };

    action sword = {
        .name = "sword",
        .name_length = 5,
        .POW = 100,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'e',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : massive garanted damage output
    };

    action provoke = {
        .name = "provoke",
        .name_length = 7,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "provoke",
            .end = 2,
        },
        .aim = 'e',
        .type = 'l',
        .superguard = false,
        .odd = 80,
        // effect : the enemy will focus Derek for 2 turns
    };  
    Derek.actions[0] = taser;  
    Derek.actions[1] = sword;
    Derek.actions[2] = provoke;

    character Flavie = { // Flavie is a mage
        .name = "Flavie",
        .name_length = 6,
        .maxHP = 120,
        .HP = 120,
        .POW = 20,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .dice = 30,
        .actions = malloc(3*sizeof(action)),
        .NOA = 3,
    };

    action hack = { 
        .name = "hack",
        .name_length = 4,
        .POW = 500,
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

    action shield = { 
        .name = "shield",
        .name_length = 6,
        .POW = 0,
        .heal = 100,
        .st = {
            .name = "defense",
            .end = 1,
        },
        .aim = 'a',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : the action protects the crew from one attack
    };

    action potion = { 
        .name = "potion",
        .name_length = 6,
        .POW = 0,
        .heal = 0,
        .st = {
            .name = "corrupt",
            .end = 1000,
        },
        .aim = 'e',
        .type = 'r',
        .superguard = false,
        .odd = 100,
        // effect : if the dragon is tased, then he looses its firebreath. Otherwise it throws the potion away
    };
    Flavie.actions[0] = hack;
    Flavie.actions[1] = shield;
    Flavie.actions[2] = potion;

    character Haloise = { // Haloïse est une naine érudite
        .name = "Haloise",
        .name_length = 7,
        .maxHP = 350,
        .HP = 350,
        .POW = 10,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .dice = 10,
        .actions = malloc(3*sizeof(action)),
        .NOA = 3,
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

    action stone = { 
        .name = "stone",
        .name_length = 5,
        .POW = 0,
        .heal = 50,
        .st = {
            .name = "defense",
            .end = 3,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : high defense
    };

    action hammer = { 
        .name = "hammer",
        .name_length = 6,
        .POW = 300,
        .heal = 0,
        .st = {
            .name = "danger",
            .end = 3,
        },
        .aim = 'i',
        .type = 'g',
        .superguard = false,
        .odd = 100,
        // effect : high damage output, but the character may receive damage
    };
    Haloise.actions[0] = encyclopedia;
    Haloise.actions[1] = stone;
    Haloise.actions[2] = hammer;

    character Chara = { // Xhara est un archer
        .name = "Xhara",
        .name_length = 5,
        .maxHP = 150,
        .HP = 150,
        .POW = 30,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .dice = 20,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };
    character Clover = { // Clover est un gobelin assassin
        .name = "Clover",
        .name_length = 6,
        .maxHP = 80,
        .HP = 80,
        .POW = 60,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .dice = 4,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };

    character* team = (character*)malloc(5*sizeof(character));
    team[0] = Derek;
    team[1] = Flavie;
    team[2] = Haloise;
    team[3] = Chara;
    team[4] = Clover;

    character Dragon = {
        .name = "Dragon",
        .name_length = 6,
        .maxHP = 1000,
        .HP = 1000,
        .POW = 0,
        .DEF = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .dice = 0,
        .actions = malloc(4*sizeof(action)),
        .NOA = 4,
    };

    action firebreath = {
        .name = "firebreath",
        .name_length = 10,
        .POW = 50,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'a',
        .superguard = false,
        .odd = 40,
    };
    action stomp = {
        .name = "stomp",
        .name_length = 5,
        .POW = 70,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'i',
        .superguard = true,
        .odd = 35,
    };
    action bite = {
        .name = "bite",
        .name_length = 4,
        .POW = 30,
        .heal = 100,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 20,
    };
    action claw = {
        .name = "claw",
        .name_length = 4,
        .POW = 1000,
        .heal = 0,
        .st = {
            .name = "normal",
            .end = -1,
        },
        .aim = 'i',
        .superguard = false,
        .odd = 5,
    };

    Dragon.actions[0] = firebreath;
    Dragon.actions[1] = stomp;
    Dragon.actions[2] = bite;
    Dragon.actions[3] = claw;

    stats s = {
        .team = team,
        .enemy = Dragon,
        .turn = 1,
    };

    return s;
}