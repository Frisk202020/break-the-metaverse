#include <stdlib.h>
#include "battle.h"

/* Initialize the stats for the dragon fight*/
stats dragon_initialize(){
    character Derek = {
        .name = "Derek",
        .name_length = 5,
        .maxHP = 250,
        .HP = 250,
        .POW = 50,
        .dice = 6,
        .actions = malloc(3*sizeof(action)),
        .NOA = 3,
    };

    action taser = {
        .name = "taser",
        .name_length = 5,
        .POW = 10,
        .heal = 0,
        .aim = 'l',
        .superguard = false,
        .odd = 30,
        // effect : stuns the enemy for the current turn
    };

    action sword = {
        .name = "sword",
        .name_length = 5,
        .POW = 100,
        .heal = 0,
        .aim = 'g',
        .superguard = false,
        .odd = 100,
        // effect : massive garanted damage output
    };

    action provoke = {
        .name = "provoke",
        .name_length = 7,
        .POW = 0,
        .heal = 0,
        .aim = 'l',
        .superguard = false,
        .odd = 80,
        // effect : the enemy will focus Derek for 2 turns
    };  
    Derek.actions[0] = taser;  
    Derek.actions[1] = sword;
    Derek.actions[2] = provoke;

    character Flavie = {
        .name = "Flavie",
        .name_length = 6,
        .maxHP = 120,
        .HP = 120,
        .POW = 20,
        .dice = 30,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };
    character Haloise = {
        .name = "Haloïse",
        .name_length = 7,
        .maxHP = 350,
        .HP = 350,
        .POW = 10,
        .dice = 10,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };
    character Chara = {
        .name = "Xhara",
        .name_length = 5,
        .maxHP = 150,
        .HP = 150,
        .POW = 30,
        .dice = 20,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };
    character Clover = {
        .name = "Clover",
        .name_length = 6,
        .maxHP = 80,
        .HP = 80,
        .POW = 60,
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
        .dice = 0,
        .actions = malloc(4*sizeof(action)),
        .NOA = 4,
    };

    action firebreath = {
        .name = "firebreath",
        .name_length = 10,
        .POW = 50,
        .heal = 0,
        .aim = 'a',
        .superguard = false,
        .odd = 40,
    };
    action stomp = {
        .name = "stomp",
        .name_length = 5,
        .POW = 70,
        .heal = 0,
        .aim = 'i',
        .superguard = true,
        .odd = 35,
    };
    action bite = {
        .name = "bite",
        .name_length = 4,
        .POW = 30,
        .heal = 100,
        .aim = 'i',
        .superguard = false,
        .odd = 20,
    };
    action claw = {
        .name = "claw",
        .name_length = 4,
        .POW = 1000,
        .heal = 0,
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
    };

    return s;
}