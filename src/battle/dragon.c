#include <stdlib.h>
#include "battle.h"

/* Initialize the stats for the dragon fight*/
stats dragon_initialize(){
    character Derek = {
        .name = "Derek",
        .maxHP = 250,
        .HP = 250,
        .POW = 50,
        .dice = 6,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };
    character Flavie = {
        .name = "Flavie",
        .maxHP = 120,
        .HP = 120,
        .POW = 20,
        .dice = 30,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };
    character Haloise = {
        .name = "Haloïse",
        .maxHP = 350,
        .HP = 350,
        .POW = 10,
        .dice = 10,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };
    character Chara = {
        .name = "Xhara",
        .maxHP = 150,
        .HP = 150,
        .POW = 30,
        .dice = 20,
        .actions = malloc(0*sizeof(action)),
        .NOA = 0,
    };
    character Clover = {
        .name = "Clover",
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
        .maxHP = 1000,
        .HP = 1000,
        .POW = 0,
        .dice = 0,
        .actions = malloc(3*sizeof(action)),
        .NOA = 3,
    };

    action firebreath = {
        .name = "firebreath",
        .POW = 50,
        .heal = 0,
        .aim = 'a',
        .superguard = false,
    };
    action stomp = {
        .name = "stomp",
        .POW = 70,
        .heal = 0,
        .aim = 'i',
        .superguard = true,
    };
    action bite = {
        .name = "bite",
        .POW = 30,
        .heal = 100,
        .aim = 'i',
        .superguard = true,
    };

    Dragon.actions[0] = firebreath;
    Dragon.actions[1] = stomp;
    Dragon.actions[2] = bite;

    stats s = {
        .team = team,
        .enemy = Dragon,
    };

    return s;
}