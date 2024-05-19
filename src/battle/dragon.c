#include <stdlib.h>
#include "battle.h"

/* Initialize the stats for the dragon fight*/
stats dragon_initialize(){
    character Derek = {
        .name = "Derek",
        .HP = 250,
        .POW = 50,
        .dice = 6,
    };
    character Flavie = {
        .name = "Flavie",
        .HP = 120,
        .POW = 20,
        .dice = 30,
    };
    character Haloise = {
        .name = "Haloïse",
        .HP = 350,
        .POW = 10,
        .dice = 10,
    };
    character Chara = {
        .name = "Xhara",
        .HP = 150,
        .POW = 30,
        .dice = 20,
    };
    character Clover = {
        .name = "Clover",
        .HP = 80,
        .POW = 60,
        .dice = 4,
    };

    character* team = (character*)malloc(5*sizeof(character));
    team[0] = Derek;
    team[1] = Flavie;
    team[2] = Haloise;
    team[3] = Chara;
    team[4] = Clover;

    character Dragon = {
        .HP = 1000,
        .POW = 0,
    };

    stats s = {
        .team = team,
        .enemy = Dragon,
    };

    return s;
}